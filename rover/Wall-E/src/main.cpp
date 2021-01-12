#include <Arduino.h>
#include <ChRt.h>
#include <Wire.h>
#include <actuator/dc_motor.h>
#include <actuator/servo.h>
#include <constants.h>
#include <sensor/adafruit_ultimate_gps.h>
#include <sensor/bmp280.h>
#include <sensor/bno055.h>
#include <sensor/ppm_receiver.h>

#include <tuple>

#include "controller/rover_controller.h"


using namespace sensor;
using namespace actuator;
gps::AdafruitUltimateGPS* rover_gps;
compass::BNO055Compass* rover_compass;
rc::PPMReceiver* ppm_rc;
motor::DCMotor* left_motor;
motor::DCMotor* right_motor;
servo::Servo* drop_servo;
controller::RoverController* rover_controller;
barometer::BMP280Barometer* bmp280;

bool connected = true;
bool led_state = false;

MUTEX_DECL(dataMutex);

static THD_WORKING_AREA(GPSThread, 1024);

static THD_FUNCTION(Thread0, arg)
{
    (void)arg;  // avoid warning on unused parameters.
    while (true)
    {
        if (connected)
        {
            // rover_gps->Read();
            chThdSleepMilliseconds(timing::GPS_TRACKING_MS);
        }
    }
}

static THD_WORKING_AREA(EstimationThread, 1024);

static THD_FUNCTION(Thread1, arg)
{
    (void)arg;  // avoid warning on unused parameters.
    while (true)
    {
        if (connected)
        {
            rover_gps->Update();
            // bmp280->Update();
            chThdSleepMilliseconds(1000);
        }
    }
}

static THD_WORKING_AREA(SlowThread, 1024);

static THD_FUNCTION(Thread2, arg)
{
    (void)arg;  // avoid warning on unused parameters.
    while (true)
    {
        if (connected)
        {
            rover_compass->Update();
            // TODO: figure out motor update frequency
            // left_motor->Update();
            // right_motor->Update();
            // drop_servo->Update();
            chThdSleepMilliseconds(timing::SLOW_TASK_MS);
        }
    }
}

void chSetup()
{
    chThdCreateStatic(GPSThread, sizeof(GPSThread), HIGHPRIO, Thread0, NULL);
    chThdCreateStatic(EstimationThread, sizeof(EstimationThread), LOWPRIO, Thread1, NULL);
    chThdCreateStatic(SlowThread, sizeof(SlowThread), NORMALPRIO, Thread2, NULL);
}

void setup()
{
    Serial.begin(115200);

    while (!Serial)
        ;  // Leonardo: wait for serial monitor
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

    rover_compass = new compass::BNO055Compass("bno055");
    rover_gps     = new gps::AdafruitUltimateGPS("gps");
    ppm_rc        = new rc::PPMReceiver("ppm rc receiver");

    rover_controller = new controller::RoverController();
    left_motor       = new motor::DCMotor("left_motor", motor::MotorMapping::LEFT_MOTOR);
    right_motor = new motor::DCMotor("right_motor", motor::MotorMapping::RIGHT_MOTOR);
    drop_servo  = new servo::Servo("servo");

    bmp280 = new barometer::BMP280Barometer(barometer::LogicMode::I2C, "barometer");

    Serial.println("=============== AUVSI Rover ======================");

    rover_compass->Attach();
    rover_gps->Attach();
    // ppm_rc->Attach();
    // left_motor->Attach();
    // right_motor->Attach();
    // drop_servo->Attach();
    bmp280->Attach();

    connected = true;
    // calibration procedure

    // rover_compass->Calibrate();
    // rover_gps->Calibrate();

    chBegin(chSetup);

    while (true)
    {
    }
}


uint32_t gpsTimer = millis();

void loop()
{
    rover_gps->Read();

    if (millis() - gpsTimer > 1000)
    {
        gpsTimer = millis();
        bmp280->Debug();
        rover_compass->Debug();
        rover_gps->Debug();


        rover_gps->Update();
    }
    
    // chThdSleepMilliseconds(1);
    chThdSleepMicroseconds(1);
    // if (connected)
    // {
    //     switch (ppm_rc->ReadRCSwitchMode())
    //     {
    //         case rc::RCSwitchMode::MANUAL:
    //         {
    //             auto rc_result = controller::RoverController::RCController(
    //                 ppm_rc->ReadThrottle(), ppm_rc->ReadYaw());
    //             auto motor_result = controller::RoverController::MotorController(
    //                 rc_result.first, rc_result.second);
    //             left_motor->ChangeInput(motor_result.first);
    //             right_motor->ChangeInput(motor_result.second);

    //             break;
    //         }
    //         case rc::RCSwitchMode::AUTO:
    //         {
    //             if (!rover_controller->GetLandingStatus())
    //             {
    //                 double accelx, accely, accelz;
    //                 std::tie(accelx, accely, accelz) = rover_compass->GetAccelVector();
    //                 rover_controller->LandingDetectionUpdate(accelx, accely, accelz);
    //                 break;
    //             }
    //             else
    //             {
    //                 if (!rover_gps->WaitForGPSConnection())
    //                 {
    //                     rover_controller->CreateWaypoint(
    //                         rover_gps->GetCurrentGPSCoordinate());
    //                 }
    //                 if (!rover_controller->FinalArrived())
    //                 {
    //                     // TODO: make the rover focus on going straight from waypoint
    //                     to
    //                     // waypoint, instead depend on GPS corrdiante.
    //                     // update the current controller
    //                     auto current_coordinate = rover_gps->GetCurrentGPSCoordinate();
    //                     auto target_coordinate =
    //                         rover_controller->UpdateWaypoint(current_coordinate);
    //                     auto auto_result = controller::RoverController::AutoController(
    //                         current_coordinate, target_coordinate);
    //                     auto motor_result =
    //                     controller::RoverController::MotorController(
    //                         auto_result.first, auto_result.second);
    //                     left_motor->ChangeInput(motor_result.first);
    //                     right_motor->ChangeInput(motor_result.second);
    //                     break;
    //                 }
    //                 // if arrived, default to TERMINATE mode.
    //             }
    //         }

    //         case rc::RCSwitchMode::TERMINATE:
    //         {
    //             // LPM, disable everything.
    //         }
    //         default:
    //             break;
    //     }
}
