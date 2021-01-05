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
            const uint8_t filter_length = 15;
            const double filter_taps[15] = { 0.02318,0.06551,0.05194,-0.03782,-0.09311,0.04331,
                                            0.31278,0.45552,0.31278, 0.04331,-0.09311,-0.03782,
                                            0.05194,0.06551,0.02318};
            imu::Vector<3> acc_history[15] = {0};
            imu::Vector<3> gyr_history[15] = {0};
            imu::Vector<3> mag_history[15] = {0};
            uint8_t put_index = 0;

           public:
            BNO055Compass(String sensor_name);

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
