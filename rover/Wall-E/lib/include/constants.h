#pragma once
#include <Arduino.h>

namespace config
{
    const static bool PERFORM_CALIBRATION = false;
    const static bool GPS_SERIAL_DEBUG    = false;
}  // namespace config
namespace timing
{
    const static int CONTROL_TASK_MS       = 100;
    const static int FAST_TASK_MS          = 1;
    const static int SLOW_TASK_MS          = 33;
    const static int GPS_IDLE_MS           = 1000;
    const static int GPS_TRACKING_MS       = 1;
    const static int STATE_MACHINE_TASK_MS = 600;
}  // namespace timing

namespace estimation
{
    const static double DEFAULT_GPS_LATITUDE  = 49.283721;
    const static double DEFAULT_GPS_LONGITUDE = -122.792589;

    // The goal GPS coordinate
    const static double DEFAULT_FINAL_LATITUDE  = 49.284492;
    const static double DEFAULT_FINAL_LONGITUDE = -122.791767;

    // The default drop location
    const static double DEFAULT_DROP_LATITUDE  = 49.284286;
    const static double DEFAULT_DROP_LONGITUDE = -122.791641;

    const static double INTERMEDIATE_WAYPOINT_THRESHOLD = 5;  // m
    const static double FINAL_WAYPOINT_THRESHOLD        = 1;  // m
    const static int WAYPOINT_NUMBER                    = 1;

    // TODO: auto tune
    // This PID is for throttle = 50
    const static double DEFAULT_KP = 0.7;
    const static double DEFAULT_KI = 0;
    const static double DEFAULT_KD = 1;

    const static double I_MAX = 90;
    const static double I_MIN = -90;

    // landing controller
    // TODO: calibrate for these numbers
    // delay = CONTROL_TASK_MS * LANDING_DETECTION_HISTORY_LENGTH / 1000 (s)
    const static int LANDING_DETECTION_HISTORY_LENGTH = 100;
    const static double LANDING_ACCEL_THRESH          = 0.7;
    const static double LANDING_ACCEL_HISTORY_THRESH  = 1.0;

    const static double DELTA_HEIGHT_THRESHOLD        = 30;
    const static double LANDING_STATUS_CONFIRM_THRESH = 0.8;  // percent
    const static double MOTOR_TURN_MIN_THRESH         = 5;    // degree
    const static double MOTOR_TURN_MAX_THRESH         = 100;  // degree
    const static double FULL_POWER                    = 100;  // percent
    const static double FULL_ANGLE                    = 180;  // degree
}  // namespace estimation

namespace magic
{
    const static double COMPASS_OFFSET     = -15;  // degree,
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
