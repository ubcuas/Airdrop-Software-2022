#pragma once

#include <sensor/sensor.h>

namespace sensor
{
    namespace compass
    {
        class BNO055Compass : public sensor::Sensor
        {
           private:
           public:
            using Sensor::Sensor;

            virtual bool CheckConnection() override;

            virtual void Attach() override;

            virtual void Update() override;

            virtual bool Calibrate() override;

            virtual void Debug() override;
        };
    }  // namespace compass

}  // namespace sensor