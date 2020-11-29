#pragma once

#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <constants.h>
#include <sensor/sensor.h>
#include <utility/imumaths.h>

#include <tuple>

namespace sensor
{
    namespace compass
    {
        class BNO055Compass : public Sensor
        {
           private:
            Adafruit_BNO055 bno055;
            double current_heading;
            imu::Vector<3> acc;
            imu::Vector<3> gyr;
            imu::Vector<3> mag;
            double ACCEL_VEL_TRANSITION = timing::SLOW_TASK_MS / 1000.0;

           public:
            using Sensor::Sensor;

            virtual bool CheckConnection() override;

            virtual void Attach() override;

            virtual void Update() override;

            virtual bool Calibrate() override;

            virtual void Debug() override;

            double GetHeading() const;

            std::tuple<double, double, double> GetAccelVector();
        };
    }  // namespace compass

}  // namespace sensor
