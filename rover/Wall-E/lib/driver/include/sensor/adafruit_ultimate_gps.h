#pragma once

#include <sensor/sensor.h>

namespace sensor
{
    namespace gps
    {
        class AdafruitUltimateGPS : public sensor::Sensor
        {
           private:
            // GPS object

           public:
            using Sensor::Sensor;

            virtual bool CheckConnection() override;

            virtual void Attach() override;

            virtual void Update() override;

            virtual bool Calibrate() override;

            virtual void Debug() override;
        };
    }  // namespace gps

}  // namespace sensor
