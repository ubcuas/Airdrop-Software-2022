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
            int throttle_channel;
            int yaw_channel;

            int calibrate_throttle_max;
            int calibrate_throttle_min;
            int calibrate_yaw_max;
            int calibrate_yaw_min;

           public:
            using Sensor::Sensor;
            int ReadThrottle();
            int ReadYaw();
            RCSwitchMode ReadRCSwitchMode();
        };


    }  // namespace rc

}  // namespace sensor
