#pragma once

#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <sensor/sensor.h>
#include <utility/imumaths.h>
namespace sensor
{
    namespace compass
    {
        class BNO055Compass : public Sensor
        {
           private:
            Adafruit_BNO055 imu;
            double current_heading;
            imu::Vector<3> acc;
            imu::Vector<3> gyr;
            imu::Vector<3> mag;

           public:
            using Sensor::Sensor;
            
            virtual bool CheckConnection() override;
            
            virtual void Attach() override;

            virtual void Update() override;

            virtual bool Calibrate() override;

            virtual void Debug() override;

            double GetHeading() const;
        };
    }  // namespace compass

}  // namespace sensor
