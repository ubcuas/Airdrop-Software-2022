/**
 * @file state_machine.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-01-12
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once
#include <actuator/dc_motor.h>
#include <actuator/servo.h>
#include <comm/oled.h>
#include <constants.h>
#include <sensor/adafruit_ultimate_gps.h>
#include <sensor/bmp280.h>
#include <sensor/bno055.h>
#include <sensor/ppm_receiver.h>

#include <memory>

#include "controller/rover_controller.h"

#define STATE_MACHINE_DEBUG true
namespace controller
{
    enum AutoState
    {
        IDLE,
        DROP,
        LAND,
        DRIVE,
        ARRIVED
    };
    class StateMachine
    {
       private:
        sensor::gps::AdafruitUltimateGPS* rover_gps;
        sensor::compass::BNO055Compass* rover_compass;
        sensor::rc::PPMReceiver* ppm_rc;
        actuator::motor::DCMotor* left_motor;
        actuator::motor::DCMotor* right_motor;
        actuator::servo::Servo* drop_servo;
        sensor::barometer::BMP280Barometer* rover_barometer;

        // objects that won't be shared
        display::OLED* rover_oled;
        controller::RoverController* rover_controller;

        AutoState current_state;

        void ManualStateMachine();
        void AutoStateMachine();

       public:
        StateMachine();
        void Calibration();
        void CheckConnection();
        void SlowUpdate();
        void FastUpdate();
        void ControlUpdate();
        void StateMachineUpdate();
        void LEDUpdate();
        void Debug();
    };
}  // namespace controller