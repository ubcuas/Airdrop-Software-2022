#include <Wire.h>
#include <pin_assignment.h>
#include <sensor/bno055.h>
#include <pin_assignment.h>
#include <Wire.h>

namespace sensor
{
    namespace compass
    {

        bool BNO055Compass::CheckConnection()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Checking Connection");
            if(bno055.begin())
            {
                Serial.println(" Connected!");
                return true;
            }
            Serial.println(" Disconnected!");
            return false;
        }

        void BNO055Compass::Attach()
        {
            bno055 = Adafruit_BNO055(55, 0x28);
            if (!bno055.begin())
            {
                Serial.print("No BNO055 detected");
                while (1)
                    ;
            }
            bno055.setExtCrystalUse(true);
            current_heading = 0;
        }

        void BNO055Compass::Update()
        {
            double sumx = 0,sumy = 0,sumz = 0;

            imu::Vector<3> euler = bno055.getVector(Adafruit_BNO055::VECTOR_EULER);
            current_heading = euler.x();

            imu::Vector<3> acc_temp = bno055.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
            imu::Vector<3> gyr_temp = bno055.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
            imu::Vector<3> mag_temp = bno055.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);

            acc_history[put_index] = acc_temp;
            gyr_history[put_index] = gyr_temp;
            mag_history[put_index] = mag_temp;

            put_index++;
            if(put_index == filter_length)
            {
                put_index = 0;
            }

            uint8_t index = put_index;

            for(uint8_t i = 0; i < filter_length; ++i)
            {
                index = (index != 0) ? index - 1 : filter_length - 1;
                sumx += filter_taps[i] * acc_history[index].x();
                sumy += filter_taps[i] * acc_history[index].y();
                sumz += filter_taps[i] * acc_history[index].z();
            }
            acc[0] = sumx;
            acc[1] = sumy;
            acc[2] = sumz;

            sumx = 0.0;
            sumy = 0.0;
            sumz = 0.0;

            for(uint8_t i = 0; i < filter_length; ++i)
            {
                index = (index != 0) ? index - 1 : filter_length - 1;
                sumx += filter_taps[i] * gyr_history[index].x();
                sumy += filter_taps[i] * gyr_history[index].y();
                sumz += filter_taps[i] * gyr_history[index].z();
            }
            gyr[0] = sumx;
            gyr[1] = sumy;
            gyr[2] = sumz;

            sumx = 0.0;
            sumy = 0.0;
            sumz = 0.0;

            for(uint8_t i = 0; i < filter_length; ++i)
            {
                index = (index != 0) ? index - 1 : filter_length - 1;
                sumx += filter_taps[i] * mag_history[index].x();
                sumy += filter_taps[i] * mag_history[index].y();
                sumz += filter_taps[i] * mag_history[index].z();
            }
            mag[0] = sumx;
            mag[1] = sumy;
            mag[2] = sumz;

        }

        bool BNO055Compass::Calibrate()
        {
            uint8_t system, gyro, accel, mg = 0;
            bno055.getCalibration(&system, &gyro, &accel, &mg);

            Serial.print(this->sensor_name);
            Serial.println(" Calibrate");
            if ((system == 0) || (gyro == 0) || (accel == 0) || (mg == 0))
            {
                return false;
            }

            return true;
        }

        void BNO055Compass::Debug()
        {
            Serial.println("Compass =================");
            Serial.print(this->sensor_name);
            Serial.println(" Debug");
            Serial.printf("Current heading: %f\n", current_heading);
            Serial.println("=================");
        }

        double BNO055Compass::GetHeading() const
        {
            return current_heading;
        }

        std::tuple<double, double, double> BNO055Compass::GetAccelVector()
        {
            return std::make_tuple(acc[0], acc[1], acc[2]);
        }

    }  // namespace compass

}  // namespace sensor
