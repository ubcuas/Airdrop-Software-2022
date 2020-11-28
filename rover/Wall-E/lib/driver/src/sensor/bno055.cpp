#include <Wire.h>
#include <pin_assignment.h>
#include <sensor/bno055.h>

namespace sensor
{
    namespace compass
    {
        bool BNO055Compass::CheckConnection()
        {
            if (imu.begin())
            {
                Serial.println(" Connected!");
                return true;
            }
            Serial.println(" Disconnected!");
            return false;
        }

        void BNO055Compass::Attach()
        {
            imu = Adafruit_BNO055(55, 0x28);
            while (!imu.begin())
            {
                Serial.println(" Connecting");
            }
            imu.setExtCrystalUse(true);
            current_heading = 0;
        }

        void BNO055Compass::Update()
        {
            acc = imu.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
            gyr = imu.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
            mag = imu.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);

            imu::Vector<3> euler = imu.getVector(Adafruit_BNO055::VECTOR_EULER);
            
            current_heading = euler.x();
        }

        bool BNO055Compass::Calibrate()
        {
            uint8_t system, gyro, accel, mg = 0;
            imu.getCalibration(&system, &gyro, &accel, &mg);

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
            Serial.printf("Current heading: %f", current_heading);
            Serial.println("=================");
        }

        double BNO055Compass::GetHeading() const
        {
            return current_heading;
        }


    }  // namespace compass

}  // namespace sensor
