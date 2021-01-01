#pragma once

#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <constants.h>
#include <sensor/sensor.h>
<<<<<<< HEAD
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
=======
#include <utility/imumaths.h>

#include <tuple>

>>>>>>> 01a00c663e643e510655256f5849c00e897c803e
namespace sensor
{
    namespace compass
    {
        class BNO055Compass : public Sensor
        {
           private:
<<<<<<< HEAD
            Adafruit_BNO055 imu = Adafruit_BNO055();
            int current_heading;
            imu::Vector<3> acc;
            imu::Vector<3> gyr;
            imu::Vector<3> mag;
=======
            Adafruit_BNO055 bno055;
            double current_heading;
            imu::Vector<3> acc;
            imu::Vector<3> gyr;
            imu::Vector<3> mag;
            double ACCEL_VEL_TRANSITION = timing::SLOW_TASK_MS / 1000.0;
>>>>>>> 01a00c663e643e510655256f5849c00e897c803e

           public:
            BNO055Compass(String sensor_name);

            virtual bool CheckConnection() override;

            virtual void Attach() override;

            virtual void Update() override;

            virtual bool Calibrate() override;

            virtual void Debug() override;

<<<<<<< HEAD
            int getHeading();
=======
            double GetHeading() const;

            std::tuple<double, double, double> GetAccelVector();
>>>>>>> 01a00c663e643e510655256f5849c00e897c803e
        };
    }  // namespace compass

}  // namespace sensor
