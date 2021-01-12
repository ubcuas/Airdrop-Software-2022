#include <Arduino.h>
#include <ChRt.h>
#include <Wire.h>

#include <tuple>

#include "controller/state_machine.h"

controller::StateMachine stateMachine;

MUTEX_DECL(dataMutex);

static THD_WORKING_AREA(GPSThread, 1024);

static THD_FUNCTION(Thread0, arg)
{
    (void)arg;  // avoid warning on unused parameters.
    while (true)
    {
        // rover_gps->Read();
        stateMachine.FastUpdate();
        chThdSleepMilliseconds(timing::GPS_TRACKING_MS);
    }
}

static THD_WORKING_AREA(EstimationThread, 1024);

static THD_FUNCTION(Thread1, arg)
{
    (void)arg;  // avoid warning on unused parameters.
    while (true)
    {
        // rover_gps->Update();
        stateMachine.SlowUpdate();
        chThdSleepMilliseconds(timing::STATE_TASK_MS);
    }
}

static THD_WORKING_AREA(SlowThread, 1024);

static THD_FUNCTION(Thread2, arg)
{
    (void)arg;  // avoid warning on unused parameters.
    while (true)
    {
        stateMachine.ControlUpdate();  // rover_compass->Update();
        // rover_barometer->Update();
        // TODO: figure out motor update frequency
        // left_motor->Update();
        // right_motor->Update();
        // drop_servo->Update();
        chThdSleepMilliseconds(timing::SLOW_TASK_MS);
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

    stateMachine = controller::StateMachine();

    chBegin(chSetup);

    while (true)
    {
    }
}


uint32_t count = 0;

void loop()
{
    // rover_barometer->Debug();
    // rover_compass->Debug();
    // rover_gps->Debug();
    // count += 1;
    chThdSleepMilliseconds(1000);

    
}
