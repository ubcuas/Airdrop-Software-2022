#pragma once
#include <Arduino.h>

namespace timing
{
    const static int ESTIMATION_TASK_MS = 250;

    const static int FAST_TASK_MS = 10;

    const static int SLOW_TASK_MS = 100;

    const static int GPS_IDLE_MS = 1000;

    const static int GPS_TRACKING_MS = 1;

    const static int STATE_TASK_MS = 500;
}  // namespace timing

namespace estimation
{
    const static double DEFAULT_GPS_LATITUDE  = 0;
    const static double DEFAULT_GPS_LONGITUDE = 0;
    const static double MOTOR_TURN_MIN_THRESH = 5;
    const static double MOTOR_TURN_MAX_THRESH = 100;
    const static double FULL_POWER            = 100;
    const static double FULL_ANGLE            = 180;
}  // namespace estimation

namespace magic
{
    const static unsigned int HIGH_READING = 1000;
    const static unsigned int LOW_READING  = 0;
    const static int AUTO_MODE             = 1000;
    const static int TERMINATE_SIGNAL      = 2000;
    const static int ERROR_MARGIN          = 100;
    const static int NUM_DEGREES           = 360;
    const static int DEGREE_RANGE          = 180;
    const static int MAX_MOTOR_INPUT       = 255;
    const static int MIN_MOTOR_INPUT       = 40;
    const static int PERCENTAGE            = 100;
}  // namespace magic
