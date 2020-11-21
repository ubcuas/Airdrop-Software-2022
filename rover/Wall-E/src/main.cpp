#include <Arduino.h>
#include <ChRt.h>
#include <actuator/dc_motor.h>
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

controller::RoverController* rover_controller;

bool connected = false;
bool led_state = false;

MUTEX_DECL(dataMutex);

static THD_WORKING_AREA(GPSThread, 64);

static THD_FUNCTION(Thread0, arg)
{
    (void)arg;  // avoid warning on unused parameters.
    while (true)
    {
        if (connected)
        {
            rover_gps->Update();
            chThdSleepMilliseconds(timing::GPS_IDLE_MS);
        }
    }
}

static THD_WORKING_AREA(EstimationThread, 64);

static THD_FUNCTION(Thread1, arg)
{
    (void)arg;  // avoid warning on unused parameters.
    while (true)
    {
        chThdSleepMilliseconds(timing::ESTIMATION_TASK_MS);
    }
}

static THD_WORKING_AREA(FastThread, 256);

static THD_FUNCTION(Thread2, arg)
{
    (void)arg;  // avoid warning on unused parameters.
    while (true)
    {
        if (connected)
        {
            chThdSleepMilliseconds(timing::FAST_TASK_MS);
            ppm_rc->Update();
        }
    }
}

static THD_WORKING_AREA(SlowThread, 64);

static THD_FUNCTION(Thread3, arg)
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
    chThdCreateStatic(FastThread, sizeof(FastThread), NORMALPRIO, Thread2, NULL);
    chThdCreateStatic(SlowThread, sizeof(SlowThread), NORMALPRIO, Thread3, NULL);
}

void setup()
{
    Serial.begin(115200);

    rover_compass = new compass::BNO055Compass("bno055");
    rover_gps     = new gps::AdafruitUltimateGPS("gps");
    ppm_rc        = new rc::PPMReceiver("ppm rc receiver");

    rover_controller = new controller::RoverController();
    left_motor       = new motor::DCMotor("left_motor", motor::MotorMapping::LEFT_MOTOR);
    right_motor      = new motor::DCMotor("right_motor", motor::MotorMapping::RIGHT_MOTOR);

    Serial.println("=============== AUVSI Rover ======================");

    rover_gps->Attach();
    rover_compass->Attach();
    ppm_rc->Attach();

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

bool has_landed = false;
bool has_arrived = false;

void loop()
{
    if (connected)
    {
        Serial.println(ppm_rc->ReadThrottle());
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
                if (!has_landed) {
                    rover_controller->LandingDetectionUpdate();
                    has_landed = rover_controller->GetLandingStatus();
                } else {
                    if (!has_arrived)
                    {
                        float turn_angle{rover_controller->HeadingController()};
                        float speed{ /* FILL IN SPEED CALCULATION */ };

                        auto motor_result{controller::RoverController::MotorController(speed, turn_angle)};
                        left_motor->ChangeInput(motor_result.first);
                        right_motor->ChangeInput(motor_result.second);

                        rover_controller->ArrivalDetectionUpdate();
                        has_arrived = rover_controller->GetArrivalStatus();
                    }
                }
                break;
            }

            case rc::RCSwitchMode::TERMINATE:
            {
            }
            default:
                break;
        }
        digitalWrite(LED_BUILTIN, led_state);
        led_state = !led_state;
        chThdSleepMilliseconds(timing::STATE_TASK_MS);
    }
}
