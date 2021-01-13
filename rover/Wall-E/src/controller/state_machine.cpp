#include <controller/state_machine.h>

using namespace sensor;
using namespace actuator;
namespace controller
{
    StateMachine::StateMachine()
    {
        // device initialization
        rover_compass = new compass::BNO055Compass("bno055");
        rover_gps     = new gps::AdafruitUltimateGPS("gps");
        ppm_rc        = new rc::PPMReceiver("ppm rc receiver");
        left_motor    = new motor::DCMotor("left_motor", motor::MotorMapping::LEFT_MOTOR);
        right_motor = new motor::DCMotor("right_motor", motor::MotorMapping::RIGHT_MOTOR);
        drop_servo  = new servo::Servo("servo");
        rover_barometer =
            new barometer::BMP280Barometer(barometer::LogicMode::I2C, "barometer");
        rover_oled = new display::OLED();

        // controller initialization
        rover_controller   = new controller::RoverController(timing::SLOW_TASK_MS);
        landing_controller = new controller::LandingController();
        planning           = new controller::Planning();



        rover_compass->Attach();
        rover_gps->Attach();
        // ppm_rc->Attach();
        // left_motor->Attach();
        // right_motor->Attach();
        // drop_servo.Attach();
        rover_barometer->Attach();
        current_state = AutoState::IDLE;
    }
    void StateMachine::Calibration()
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
    void StateMachine::CheckConnection() {}
    void StateMachine::SlowUpdate()
    {
        rover_barometer->Update();
        rover_compass->Update();
        
        landing_controller->LandingDetectionUpdate(rover_compass->GetAccelVector());
        rover_controller->RoverControllerUpdate(
            rover_compass->GetAccelVector(), rover_compass->GetOrientationAccelVector(),
            rover_compass->GetEulerVector());
    }
    void StateMachine::FastUpdate()
    {
        rover_gps->Read();
    }
    void StateMachine::ControlUpdate()
    {
        rover_gps->Update();
        // left_motor->Update();
        // right_motor->Update();
        // drop_servo->Update();
    }
    void StateMachine::LEDUpdate() {}
    void StateMachine::Debug()
    {
        // rover_barometer->Debug();
        rover_compass->Debug();
        // rover_gps->Debug();
        // landing_controller->Debug();
        rover_controller->Debug();

        display::oled_dict data;
        data.x = rover_controller->q[0];
        data.y = rover_controller->q[1];
        data.heading   = rover_compass->GetHeading();
        data.latitude  = rover_gps->GetCurrentGPSCoordinate().first;
        data.longitude = rover_gps->GetCurrentGPSCoordinate().second;
        data.altitude  = rover_barometer->GetAltitude();
        data.state     = auto_state_name[current_state];
        // Serial.printf("[Count]: %ld\n", count);
        rover_oled->displayDebugMessage(&data);
    }
    void StateMachine::ManualStateMachine()
    {
        auto rc_result = controller::RoverController::RCController(ppm_rc->ReadThrottle(),
                                                                   ppm_rc->ReadYaw());
        auto motor_result = controller::RoverController::MotorController(
            rc_result.first, rc_result.second);
        left_motor->ChangeInput(motor_result.first);
        right_motor->ChangeInput(motor_result.second);
    }
    void StateMachine::AutoStateMachine()
    {
        switch (current_state)
        {
            // TODO: communication between winch and rover for dropping
            case AutoState::IDLE:
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
                    current_state = AutoState::DRIVE;
                    landing_controller->End();
                }
                break;
            }
            case AutoState::DRIVE:
            {
                // TODO: testing
                return;

                if (!rover_gps->WaitForGPSConnection())
                {
                    planning->CreateWaypoint(rover_gps->GetCurrentGPSCoordinate());
                }
                if (!planning->FinalArrived())
                {
                    // TODO: make the rover focus on going straight from waypoint to
                    // waypoint, instead depend on GPS corrdiante. update the current
                    // controller
                    auto current_coordinate = rover_gps->GetCurrentGPSCoordinate();
                    auto target_coordinate = planning->UpdateWaypoint(current_coordinate);
                    auto auto_result       = controller::RoverController::AutoController(
                        current_coordinate, target_coordinate);
                    auto motor_result = controller::RoverController::MotorController(
                        auto_result.first, auto_result.second);
                    left_motor->ChangeInput(motor_result.first);
                    right_motor->ChangeInput(motor_result.second);
                }
                else
                {
                    current_state = AutoState::ARRIVED;
                }
                break;
            }
            case AutoState::ARRIVED:
            {
                // TODO: display something?
            }
            default:
                break;
        }
    }
    void StateMachine::StateMachineUpdate()
    {
        if (ppm_rc->CheckConnection())
        {
            // TODO: the reset between states
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