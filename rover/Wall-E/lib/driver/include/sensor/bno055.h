/**
 * @file bno055.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-01-11
 *  Board layout:
         +----------+
         |         *| RST   PITCH  ROLL  HEADING
     ADR |*        *| SCL
     INT |*        *| SDA     ^            /->
     PS1 |*        *| GND     |            |
     PS0 |*        *| 3VO     Y    Z-->    \-X
         |         *| VIN
         +----------+

Absolute Orientation (Euler Vector, 100Hz)
- Three axis orientation data based on a 360° sphere
Absolute Orientation (Quaterion, 100Hz)
- Four point quaternion output for more accurate data manipulation
Angular Velocity Vector (100Hz)
- Three axis of 'rotation speed' in rad/s
Acceleration Vector (100Hz)
- Three axis of acceleration (gravity + linear motion) in m/s^2
Magnetic Field Strength Vector (20Hz)
- Three axis of magnetic field sensing in micro Tesla (uT)
Linear Acceleration Vector (100Hz)
- Three axis of linear acceleration data (acceleration minus gravity) in m/s^2
Gravity Vector (100Hz)
- Three axis of gravitational acceleration (minus any movement) in m/s^2
Temperature (1Hz)
- Ambient temperature in degrees celsius

 * @copyright Copyright (c) 2021
 *
 */
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

            /**
             * @brief Return the linear acceleration. Not including the gravity.
             *
             * @return std::tuple<double, double, double>
             */
            std::tuple<double, double, double> GetAccelVector();

            /**
             * @brief Return the Euler. Not including the gravity.
             *
             * @return std::tuple<double, double, double>
             */
            std::tuple<double, double, double> GetOrientationAccelVector();

            /**
             * @brief Get the Euler Vector object
             * 
             * @return std::tuple<double, double, double> 
             */
            std::tuple<double, double, double> GetEulerVector();
        };
    }  // namespace compass

}  // namespace sensor
