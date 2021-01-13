#include <Arduino.h>
#include <ChRt.h>
#include <Wire.h>

#include <tuple>

#include "controller/state_machine.h"

controller::StateMachine* state_machine;

MUTEX_DECL(dataMutex);

static THD_WORKING_AREA(FAST_THREAD, 1024);

static THD_FUNCTION(Thread0, arg)
{
    (void)arg;  // avoid warning on unused parameters.
    while (true)
    {
        state_machine->FastUpdate();
        chThdSleepMilliseconds(timing::GPS_TRACKING_MS);
    }
}

static THD_WORKING_AREA(CONTROL_THREAD, 1024);

static THD_FUNCTION(Thread1, arg)
{
    (void)arg;  // avoid warning on unused parameters.
    while (true)
    {
        state_machine->ControlUpdate();
        chThdSleepMilliseconds(timing::ESTIMATION_TASK_MS);
    }
}

static THD_WORKING_AREA(SLOW_THREAD, 1024);

static THD_FUNCTION(Thread2, arg)
{
    (void)arg;  // avoid warning on unused parameters.
    while (true)
    {
        state_machine->SlowUpdate();
        // TODO: figure out motor update frequency

        chThdSleepMilliseconds(timing::SLOW_TASK_MS);
    }
}

void chSetup()
{
    chThdCreateStatic(FAST_THREAD, sizeof(FAST_THREAD), HIGHPRIO, Thread0, NULL);
    chThdCreateStatic(CONTROL_THREAD, sizeof(CONTROL_THREAD), LOWPRIO, Thread1, NULL);
    chThdCreateStatic(SLOW_THREAD, sizeof(SLOW_THREAD), NORMALPRIO, Thread2, NULL);
}

void setup()
{
    Serial.begin(115200);

    state_machine = new controller::StateMachine();

    chBegin(chSetup);

    while (true)
    {
    }
}

uint32_t count = 0;

void loop()
{
    // state_machine->StateMachineUpdate();
    state_machine->Debug();
    chThdSleepMilliseconds(timing::STATE_TASK_MS);
}
