#include <controller/state_machine.h>

using namespace sensor;
using namespace actuator;
namespace controller
{
    StateMachine::StateMachine()
    {
        // device initialization
        rover_compass   = new compass::BNO055Compass("bno055");
        rover_gps       = new gps::AdafruitUltimateGPS("gps");
        ppm_rc          = new rc::PPMReceiver("ppm rc receiver");
        left_motor      = new motor::DCMotor("left_motor", motor::MotorMapping::LEFT_MOTOR);
        right_motor     = new motor::DCMotor("right_motor", motor::MotorMapping::RIGHT_MOTOR);
        drop_servo      = new servo::Servo("servo");
        rover_barometer = new barometer::BMP280Barometer(barometer::LogicMode::I2C, "barometer");
        rover_oled      = new display::OLED();

        // controller initialization
        rover_controller   = new controller::RoverController(timing::SLOW_TASK_MS);
        landing_controller = new controller::LandingController();
        planning           = new controller::Planning();

        // GPS related variables
        current_coordinate =
            std::make_pair(estimation::DEFAULT_DROP_LATITUDE, estimation::DEFAULT_DROP_LONGITUDE);
        last_coordinate =
            std::make_pair(estimation::DEFAULT_DROP_LATITUDE, estimation::DEFAULT_DROP_LONGITUDE);
        target_coordinate =
            std::make_pair(estimation::DEFAULT_FINAL_LATITUDE, estimation::DEFAULT_FINAL_LONGITUDE);

        rover_compass->Attach();
        rover_gps->Attach();
        // ppm_rc->Attach();
        left_motor->Attach();
        right_motor->Attach();
        // drop_servo.Attach();
        rover_barometer->Attach();
        current_state = AutoState::IDLE;
    }
    void StateMachine::Calibration() {}
    void StateMachine::CheckConnection()
    {
        Serial.println("\nI2C Scanner");

        Wire.begin();
        Wire1.begin();
        byte error, address;
        int nDevices;

        Serial.println("Scanning...");

        nDevices = 0;
        for (address = 1; address < 127; address++)
        {
            // The i2c_scanner uses the return value of
            // the Write.endTransmisstion to see if
            // a device did acknowledge to the address.
            Wire.beginTransmission(address);
            Wire1.beginTransmission(address);
            error = Wire.endTransmission();
            error &= Wire1.endTransmission();
            if (error == 0)
            {
                Serial.print("I2C device found at address 0x");
                if (address < 16)
                    Serial.print("0");
                Serial.print(address, HEX);
                Serial.println("  !");

                nDevices++;
            }
            else if (error == 4)
            {
                Serial.print("Unknown error at address 0x");
                if (address < 16)
                    Serial.print("0");
                Serial.println(address, HEX);
            }
        }
        if (nDevices == 0)
            Serial.println("No I2C devices found\n");
        else
            Serial.println("done\n");
    }
    void StateMachine::SlowUpdate()
    {
        rover_barometer->Update();
        rover_compass->Update();

        landing_controller->LandingDetectionUpdate(rover_compass->GetAccelVector());

        rover_controller->RoverControllerUpdate(rover_compass->GetAccelVector(),
                                                rover_compass->GetOrientationAccelVector(),
                                                rover_compass->GetEulerVector());
        if (current_state == AutoState::DRIVE)
        {
            auto auto_result = rover_controller->HeadingPIDController(
                current_coordinate, target_coordinate, rover_compass->GetHeading(),
                sensor::gps::GPSCoordinate::GetDistanceBetween(
                    sensor::gps::GPSCoordinate(current_coordinate.first, current_coordinate.second),
                    sensor::gps::GPSCoordinate(target_coordinate.first, target_coordinate.second)));
            motor_result = controller::RoverController::MotorController(auto_result);
            left_motor->ChangeInput(motor_result.first);
            right_motor->ChangeInput(motor_result.second);
        }
    }

    void StateMachine::FastUpdate()
    {
        rover_gps->Read();
    }
    void StateMachine::ControlUpdate()
    {
        left_motor->Update();
        right_motor->Update();
        // TODO: add servo back
        // drop_servo->Update();
    }
    void StateMachine::LEDUpdate() {}
    void StateMachine::Debug()
    {
        display::oled_dict data;
        data.calibration = rover_compass->compass_calibration;
        data.distance    = sensor::gps::GPSCoordinate::GetDistanceBetween(
            sensor::gps::GPSCoordinate(current_coordinate.first, current_coordinate.second),
            sensor::gps::GPSCoordinate(target_coordinate.first, target_coordinate.second));
        data.compass_heading = rover_compass->GetHeading();
        data.target_heading  = sensor::gps::GPSCoordinate::GetHeadingBetween(
            sensor::gps::GPSCoordinate(current_coordinate.first, current_coordinate.second),
            sensor::gps::GPSCoordinate(target_coordinate.first, target_coordinate.second));
        data.gps_fix   = rover_gps->CheckConnection();
        data.latitude  = current_coordinate.first;
        data.longitude = current_coordinate.second;
        data.altitude  = rover_barometer->GetAltitude();
        data.state     = auto_state_name[current_state];

        if (!config::NO_OLED_OUTPUT)
        {
            rover_oled->displayDebugMessage(&data);
        }

        if (!config::NO_SERIAL_OUTPUT)
        {
            // rover_barometer->Debug();
            rover_compass->Debug();
            rover_gps->Debug();
            // landing_controller->Debug();
            rover_controller->Debug();

            Serial.printf("[State Machine]\n==========\n");
            Serial.printf("GPS fix: %s\n", rover_gps->CheckConnection() ? "True" : "False");
            Serial.printf("Target coordinate: %f, %f\n", target_coordinate.first,
                          target_coordinate.second);
            Serial.printf("Current coordinate: %f, %f\n", current_coordinate.first,
                          current_coordinate.second);
            Serial.printf("Next waypoint: %f, %f\n", planning->GetNextWayPoint().first,
                          planning->GetNextWayPoint().second);
            Serial.printf("distance: %f\n", data.distance);
            Serial.printf("target_heading: %f\n", data.target_heading);
        }
    }
    void StateMachine::ManualStateMachine()
    {
        auto rc_result =
            controller::RoverController::RCController(ppm_rc->ReadThrottle(), ppm_rc->ReadYaw());
        auto motor_result = controller::RoverController::MotorController(rc_result);
        left_motor->ChangeInput(motor_result.first);
        right_motor->ChangeInput(motor_result.second);
    }

    void StateMachine::AutoStateMachine()
    {
        switch (current_state)
        {
            // TODO: communication between winch and rover for dropping
            case AutoState::IDLE:
                left_motor->StopMotor();
                right_motor->StopMotor();
                current_state = AutoState::DROP;
                break;
            case AutoState::DROP:
                current_state = AutoState::LAND;
                landing_controller->Start();
                break;
            case AutoState::LAND:
            {
                if (landing_controller->GetLandingStatus())
                {
                    // TODO: do more checks with barometer and GPS
                    // drop_servo->ChangeInput();
                    current_state = AutoState::CALIBRATE;
                    landing_controller->End();
                }
                break;
            }
            case AutoState::CALIBRATE:
            {
                if (rover_compass->compass_calibration == 3 && rover_gps->CheckConnection())
                {
                    current_state = AutoState::DRIVE;
                }
            }
            case AutoState::DRIVE:
            {
                if (rover_gps->CheckConnection())
                {
                    planning->CreateWaypoint(current_coordinate);

                    target_coordinate = planning->UpdateWaypoint(current_coordinate);
                }
                else
                {
                    // GPS denied
                    // Fully heading based control.
                }
                if (planning->final_arrived)
                {
                    current_state = AutoState::ARRIVED;
                }

                break;
            }
            case AutoState::ARRIVED:
            case AutoState::TERMINATE:
            {
                // TODO: display something?
                left_motor->StopMotor();
                right_motor->StopMotor();
            }
            default:
                break;
        }
    }
    void StateMachine::StateMachineUpdate()
    {
        rover_gps->Update();
        current_coordinate = rover_gps->GetCurrentGPSCoordinate();
        last_coordinate    = rover_gps->GetLastGPSCoordinate();

        if (ppm_rc->CheckConnection())
        {
            // TODO: add reset between states
            switch (ppm_rc->ReadRCSwitchMode())
            {
                case rc::RCSwitchMode::MANUAL:
                {
                    ManualStateMachine();
                    break;
                }
                case rc::RCSwitchMode::AUTO:
                {
                    AutoStateMachine();
                    break;
                }

                case rc::RCSwitchMode::TERMINATE:
                {
                    // LPM, disable everything.
                }
                default:
                    break;
            }
        }
        else
        {
            AutoStateMachine();
        }
    }
}  // namespace controller