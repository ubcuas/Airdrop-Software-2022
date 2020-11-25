#pragma once

#include <sensor/sensor.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
namespace sensor
{
    namespace compass
    {
        class BNO055Compass : public Sensor
        {
           private:
            Adafruit_BNO055 imu = Adafruit_BNO055();
            int current_heading;

           public:
            BNO055Compass(String sensor_name);

            virtual bool CheckConnection() override;

            virtual void Attach() override;

            virtual void Update() override;

            virtual bool Calibrate() override;

            virtual void Debug() override;

            int getHeading();
        };
    }  // namespace compass

}  // namespace sensor
