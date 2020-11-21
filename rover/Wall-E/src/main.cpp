#include <Arduino.h>
#include <ChRt.h>
#include <actuator/dc_motor.h>
#include <actuator/servo.h>
#include <constants.h>
#include <sensor/adafruit_ultimate_gps.h>
#include <sensor/bno055.h>
#include <sensor/ppm_receiver.h>

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

bool connected = true;
bool led_state = false;

MUTEX_DECL(dataMutex);

static THD_WORKING_AREA(GPSThread, 32);

static THD_FUNCTION(Thread0, arg)
{
    (void)arg;  // avoid warning on unused parameters.
    while (true)
    {
        if (connected)
        {
            rover_gps->Read();
            chThdSleepMilliseconds(timing::GPS_TRACKING_MS);
        }
    }
}

static THD_WORKING_AREA(EstimationThread, 32);

static THD_FUNCTION(Thread1, arg)
{
    (void)arg;  // avoid warning on unused parameters.
    while (true)
    {
        if (connected)
        {
            rover_gps->Update();
            chThdSleepMilliseconds(timing::ESTIMATION_TASK_MS);
        }
    }
}

static THD_WORKING_AREA(SlowThread, 64);

static THD_FUNCTION(Thread2, arg)
{
    (void)arg;  // avoid warning on unused parameters.
    while (true)
    {
        if (connected)
        {
            rover_compass->Update();

            // TODO: figure out motor update frequency
            left_motor->Update();
            right_motor->Update();
            drop_servo->Update();
            // connected &= rover_compass->CheckConnection();
            // connected &= rover_gps->CheckConnection();
            // connected &= ppm_rc->CheckConnection();
            // connected &= rover_compass->CheckConnection();
            // connected = true;
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

    // rover_compass = new compass::BNO055Compass("bno055");
    rover_gps = new gps::AdafruitUltimateGPS("gps");
    // ppm_rc        = new rc::PPMReceiver("ppm rc receiver");

    rover_controller = new controller::RoverController();
    left_motor       = new motor::DCMotor("left_motor", motor::MotorMapping::LEFT_MOTOR);
    right_motor = new motor::DCMotor("right_motor", motor::MotorMapping::RIGHT_MOTOR);
    drop_servo  = new servo::Servo("servo");

    Serial.println("=============== AUVSI Rover ======================");

    rover_gps->Attach();
    rover_compass->Attach();
    ppm_rc->Attach();
    drop_servo->Attach();

    connected = true;
    // calibration procedure

    rover_compass->Calibrate();
    rover_gps->Calibrate();


    pinMode(LED_BUILTIN, OUTPUT);

    chBegin(chSetup);

    while (true)
    {
    }
}

uint32_t gpsTimer = millis();

void loop()
{
    if (connected)
    {
        switch (ppm_rc->ReadRCSwitchMode())
        {
            case rc::RCSwitchMode::MANUAL:
            {
                auto rc_result = controller::RoverController::RCController(
                    ppm_rc->ReadThrottle(), ppm_rc->ReadYaw());
                auto motor_result = controller::RoverController::MotorController(
                    rc_result.first, rc_result.second);
                left_motor->ChangeInput(motor_result.first);
                right_motor->ChangeInput(motor_result.second);

                break;
            }
            case rc::RCSwitchMode::AUTO:
            {
                break;
            }

            case rc::RCSwitchMode::TERMINATE:
            {
            }
            default:
                break;
        }

        rover_gps->Read();

        if (millis() - gpsTimer > 1000)
        {
            gpsTimer = millis();

            rover_gps->Update();
        }
    }
}
