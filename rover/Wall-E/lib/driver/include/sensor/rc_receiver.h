#pragma once

#include <sensor/rc_switch_mode.h>
#include <sensor/sensor.h>

namespace sensor
{
    namespace rc
    {
        class RCRecevier : sensor::Sensor
        {
           private:
            int throttle_channel;
            int yaw_channel;
            int calibrate_throttle_max;
            int calibrate_throttle_min;
            int calibrate_yaw_max;
            int calibrate_yaw_min;

           public:
            RCRecevier(String sensor_name);
            int ReadThrottle();
            int ReadYaw();
            RCSwitchMode ReadRCSwtichMode();
        };
    }  // namespace rc

}  // namespace sensor
