#pragma once
#include <Arduino.h>

namespace timing
{
    const static int ESTIMATION_TASK_MS = 250;
    const static int FAST_TASK_MS       = 10;

    const static int SLOW_TASK_MS = 150;

    const static int GPS_IDLE_MS = 1000;

    const static int GPS_TRACKING_MS = 1;

    const static int STATE_TASK_MS = 600;
}  // namespace timing

namespace estimation
{
    const static double DEFAULT_GPS_LATITUDE            = 0;
    const static double DEFAULT_GPS_LONGITUDE           = 0;
    const static double DEFAULT_FINAL_LATITUDE          = 0;
    const static double DEFAULT_FINAL_LONGITUDE         = 0;
    const static double INTERMEDIATE_WAYPOINT_THRESHOLD = 5;  // m
    const static double FINAL_WAYPOINT_THRESHOLD        = 1;  // m
    const static int WAYPOINT_NUMBER                    = 10;
    const static int LANDING_DETECTION_HISTORY_LENGTH   = 100;
    const static double DELTA_HEIGHT_THRESHOLD          = 30;
    const static double LANDING_ACCEL_THRESH            = 0.1;
    const static double LANDING_STATUS_CONFIRM_THRESH   = 0.8;  // percent
    const static double MOTOR_TURN_MIN_THRESH           = 5;    // degree
    const static double MOTOR_TURN_MAX_THRESH           = 100;  // degree
    const static double FULL_POWER                      = 100;  // percent
    const static double FULL_ANGLE                      = 180;  // degree
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

namespace config
{
    const static int SCREEN_WIDTH  = 128;
    const static int SCREEN_HEIGHT = 32;
    const static int OLED_RESET    = 4;
}  // namespace config
