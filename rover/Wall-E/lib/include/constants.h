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
    const static double DEFAULT_GPS_LATITUDE = 0;
    const static double DEFAULT_GPS_LONGITUDE = 0;
}  // namespace estimation
