#include <sensor/bno055.h>
#include <pin_assignment.h>
#include <Wire.h>

namespace sensor
{
    namespace compass
    {

        BNO055Compass::BNO055Compass(String sensor_name)
        : Sensor::Sensor(sensor_name)
        {
            imu.setExtCrystalUse(true);
            current_heading = 0;
        }

        bool BNO055Compass::CheckConnection()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Checking Connection");
            if(imu.begin())
            {
                Serial.println(" Connected!");
                return true;
            }
            Serial.println(" Disconnected!");
            return false;
        }

        void BNO055Compass::Attach()
        {
            Wire.setSCL(pin::BNO055_SCL); 
            Wire.setSDA(pin::BNO055_SDA); 
            Wire.beginTransmission(0x28);
            imu.begin();
            Serial.print(this->sensor_name);
            Serial.println(" Attach");
        }

        void BNO055Compass::Update()
        {
            acc = imu.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
            gyr = imu.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
            mag = imu.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);

            current_heading = atan2(mag.y(),mag.x());
            Serial.print(this->sensor_name);
            Serial.println(" Update");
        }

        bool BNO055Compass::Calibrate()
        {
            uint8_t system, gyro, accel, mg = 0;
            imu.getCalibration(&system, &gyro, &accel, &mg);

            Serial.print(this->sensor_name);
            Serial.println(" Calibrate");
            if((system == 0)||(gyro == 0)||(accel==0)||(mg==0))
            {
                return false;
            }

            return true;
        }

        void BNO055Compass::Debug()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Debug");
        }

        int BNO055Compass::getHeading()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Get Heading");
            return current_heading;
        }


    }  // namespace compass

}  // namespace sensor
