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
            const double filter_taps[15] = {  -0.005071,
                                              0.011302,
                                              0.016822,
                                              -0.029808,
                                              -0.065989,
                                              0.051410,
                                              0.302127,
                                              0.438786,
                                              0.302127,
                                              0.051410,
                                              -0.065989,
                                              -0.029808,
                                              0.016822,
                                              0.011303,
                                              -0.005071};

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
