/**
 * @file rc_receiver.h
 * @brief
 * @version 1.0
 * @date 2021-01-17
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include <sensor/sensor.h>

namespace sensor
{
    namespace rc
    {
        enum class RCSwitchMode
        {
            TERMINATE,
            AUTO,
            MANUAL
        };

        class RCReceiver : public Sensor
        {
           protected:
            int throttle_channel_value;
            int yaw_channel_value;
            int switch_channel_value;

            // constants after calibrating the RC input.
            int calibrate_throttle_max;
            int calibrate_throttle_min;
            int calibrate_yaw_max;
            int calibrate_yaw_min;
            int mode_thresh_terminate;
            int mode_thresh_auto;
            int mode_thresh_manual;

           public:
            using Sensor::Sensor;
            int ReadThrottle();
            int ReadYaw();
            RCSwitchMode ReadRCSwitchMode();
        };


    }  // namespace rc

}  // namespace sensor
