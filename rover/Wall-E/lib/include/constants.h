/**
 * @file constants.h
 * @brief All the constants in the code. Also include the Arduino header for convenience
 * @version 1.0
 * @date 2021-01-17
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include "Arduino.h"
namespace config
{
    /**
     * @brief this is for system wise configuration. It will determine certain behaviors
     * of the system to change. Check these before build, make sure that it's the correct
     * config for the build.
     *
     */
    const static bool PERFORM_CALIBRATION = false;  // Enable calibration
    const static bool GPS_SERIAL_DEBUG =
        false;  // Enable GPS raw serial reading echo. Check if GPS is ok
    const static bool NO_SERIAL_OUTPUT = false;  // Disable Serial output

    const static bool NO_OLED_OUTPUT = false;
    const static int SCREEN_WIDTH    = 128;
    const static int SCREEN_HEIGHT   = 32;
    const static int OLED_RESET      = 4;
}  // namespace config
namespace timing
{
    /**
     * @brief All Thread timing related constants. Unit is milliseconds
     *
     */
    const static int CONTROL_TASK_MS       = 100;
    const static int FAST_TASK_MS          = 1;
    const static int SLOW_TASK_MS          = 33;
    const static int GPS_IDLE_MS           = 1000;
    const static int GPS_TRACKING_MS       = 1;
    const static int STATE_MACHINE_TASK_MS = 750;
}  // namespace timing

namespace estimation
{
    /**
     * @brief all state, estimation, gps, motor, controller related constants.
     *
     * TODO: clean this up
     */
    // The goal GPS coordinate
    const static double DEFAULT_FINAL_LATITUDE  = 49.2843990;
    const static double DEFAULT_FINAL_LONGITUDE = -122.7921191;

    // The default drop location
    const static double DEFAULT_DROP_LATITUDE  = 49.284286;
    const static double DEFAULT_DROP_LONGITUDE = -122.791641;

    const static double INTERMEDIATE_WAYPOINT_THRESHOLD = 5;    // m
    const static double FINAL_SLOW_DOWN_THRESH          = 3;    // m
    const static double FINAL_WAYPOINT_THRESHOLD        = 0.7;  // m
    const static int WAYPOINT_NUMBER                    = 1;

    const static int FAST_SPEED = 70;
    const static int SLOW_SPEED = 45;

    // TODO: auto tune
    // This PID is for throttle = 50
    const static double DEFAULT_KP = 0.7;
    const static double DEFAULT_KI = 0;
    const static double DEFAULT_KD = 1;

    const static double I_MAX = 90;   // "degrees"
    const static double I_MIN = -90;  // "degrees"

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
    /**
     * @brief The magic numbers.
     *
     */
    const static double COMPASS_OFFSET     = 15;  // degree,
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
