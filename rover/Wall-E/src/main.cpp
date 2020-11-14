#include <Arduino.h>
#include <ChRt.h>
#include <constants.h>
#include <sensor/adafruit_ultimate_gps.h>
#include <sensor/bno055.h>
#include <sensor/ppm_receiver.h>
#include <actuator/dc_motor.h>

using namespace sensor;
using namespace actuator;
gps::AdafruitUltimateGPS* rover_gps;
compass::BNO055Compass* rover_compass;
rc::PPMReceiver* ppm_rc;
motor::DCMotor* left_motor;
motor::DCMotor* right_motor;

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
            connected &= rover_compass->CheckConnection();
            connected &= rover_gps->CheckConnection();
            connected &= ppm_rc->CheckConnection();
            connected &= rover_compass->CheckConnection();
            connected = true;
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
    left_motor    = new motor::DCMotor("left_motor", motor::MotorMapping::LEFT_MOTOR);
    left_motor    = new motor::DCMotor("left_motor", motor::MotorMapping::LEFT_MOTOR);
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

void loop()
{
    if (connected)
    {
        Serial.println(ppm_rc->ReadThrottle());
        switch (ppm_rc->ReadRCSwitchMode())
        {
            case rc::RCSwitchMode::MANUAL:
                break;
            case rc::RCSwitchMode::AUTO:
                break;
            case rc::RCSwitchMode::TERMINATE:

            default:
                break;
        }
        digitalWrite(LED_BUILTIN, led_state);
        led_state = !led_state;
        chThdSleepMilliseconds(timing::STATE_TASK_MS);
    }
}
