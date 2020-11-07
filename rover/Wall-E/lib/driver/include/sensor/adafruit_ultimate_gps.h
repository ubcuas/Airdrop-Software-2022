#pragma once

#include <sensor/sensor.h>

namespace sensor
{
    namespace gps
    {
        class AdafruitUltimateGPS : sensor::Sensor
        {
           private:
            // GPS object

           public:
            AdafruitUltimateGPS(String sensor_name);
        };
    }  // namespace gps

}  // namespace sensor
