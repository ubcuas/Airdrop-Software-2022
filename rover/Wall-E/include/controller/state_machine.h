/**
 * @file state_machine.h
 * @brief
 * @version 1.0
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

#include "controller/landing_controller.h"
#include "controller/planning.h"
#include "controller/rover_controller.h"

#define STATE_MACHINE_DEBUG true
namespace controller
{
    // This is a very ugly and lame way to map Enum to string. However, the alternative
    // are unnecessarily complicated
    const String auto_state_name[7] = {"IDLE",  "DROP",    "LAND",     "CALIBRATE",
                                       "DRIVE", "ARRIVED", "TERMINATE"};
    enum AutoState
    {
        /**
         * @brief The default state. Should be the state to be in when flying and before dropping.
         * Trigger to DROP by a external signal
         */
        IDLE,

        /**
         * @brief The dropping state, should transit to LAND right away. However, if communication
         * is established, then this is where it tells the winch that rover has not yet landed
         */
        DROP,

        /**
         * @brief landing state, check if the rover is landed.
         *
         */
        LAND,
        /**
         * @brief Calibrate sensor state. Check the IMU, compass, GPS readings.
         *
         */
        CALIBRATE,
        /**
         * @brief Go WALL-E GO
         */
        DRIVE,
        /**
         * @brief Mission complete
         */
        ARRIVED,
        /**
         * @brief NOOOOOOOOOOO:
         * https://www.google.com/url?sa=i&url=https%3A%2F%2Fm.youtube.com%2Fwatch%3Fv%3DoDtzyq7-8sE&psig=AOvVaw3iKHOotLrjqT8utYnHuVjw&ust=1611022838706000&source=images&cd=vfe&ved=0CAIQjRxqFwoTCOjtl_S1pO4CFQAAAAAdAAAAABAE
         *
         */
        TERMINATE
    };
    // TODO add Low power state
    class StateMachine
    {
       private:
        // drivers
        sensor::gps::AdafruitUltimateGPS* rover_gps;
        sensor::compass::BNO055Compass* rover_compass;
        sensor::rc::PPMReceiver* ppm_rc;
        actuator::motor::DCMotor* left_motor;
        actuator::motor::DCMotor* right_motor;
        actuator::servo::Servo* drop_servo;
        sensor::barometer::BMP280Barometer* rover_barometer;
        display::OLED* rover_oled;

        // controllers
        controller::RoverController* rover_controller;
        controller::LandingController* landing_controller;
        controller::Planning* planning;
        AutoState current_state;
        std::pair<double, double> motor_result;

        // GPS realted data
        std::pair<double, double> current_coordinate;
        std::pair<double, double> last_coordinate;
        std::pair<double, double> target_coordinate;

        /**
         * @brief manually use RC to drive the rover around. It's also the fall back after
         * manual take over in case of things go wrong
         *
         */
        void ManualStateMachine();

        /**
         * @brief autonomous driving state machine.
         *
         */
        void AutoStateMachine();

       public:
        StateMachine();
        /**
         * @brief calibration procedure
         * TODO: finish this module
         */
        void Calibration();

        /**
         * @brief
         * TODO: finish this module
         */
        void CheckConnection();

        /**
         * @brief We use time-driven system with a bit of event-driven within it's
         * framework
         *
         * All the XXXUpdate() functions are called at certain frequency, namely at
         * 1000 / XXX_TASK_MS Hz.
         *
         * Note that all the Update functions should not have Serial.print(), delay()  or
         * any time consumping function.
         */
        /**
         * @brief Slow sensor update
         * IMU and barometer updates
         */
        void SlowUpdate();

        /**
         * @brief Fast sensor update
         * The fast updating loop in the system. It's the GPS callback, as well XBee.
         *
         */
        void FastUpdate();

        /**
         * @brief Actuator update.
         * Since actuators such as motor takes time to get to the position that it's
         * requested (in our case, relative speed). This time-driven update is depended on
         * the slowest reponse time out of al actuators
         *
         * Since the bottole neck for estimation is the control loop, estimation callbacks
         * should be included here as well
         */
        void ControlUpdate();

        /**
         * @brief State machien update
         *
         */
        void StateMachineUpdate();

        /**
         * @brief LED controlling thread
         * 1 blink every 2 seconds: IDLE
         * 2 quick consecutive blink every 2 seconds: Landind detection
         * 1 blink every 1 seconds: In Drive state, currently driving
         * 2 quick consecutive blink every 1 second: In Drive state with GPS fix
         * 3 blinks every 1 seconds: some sensor were disconnected
         */
        void LEDUpdate();

        void Debug();
    };
}  // namespace controller