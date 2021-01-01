#include <Wire.h>
#include <pin_assignment.h>
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
<<<<<<< HEAD
            Serial.print(this->sensor_name);
            Serial.println(" Checking Connection");
            if(imu.begin())
=======
            if (bno055.begin())
>>>>>>> 01a00c663e643e510655256f5849c00e897c803e
            {
                Serial.println(" Connected!");
                return true;
            }
            Serial.println(" Disconnected!");
            return false;
        }

        void BNO055Compass::Attach()
        {
<<<<<<< HEAD
            Wire.setSCL(pin::BNO055_SCL); 
            Wire.setSDA(pin::BNO055_SDA); 
            Wire.beginTransmission(0x28);
            imu.begin();
            Serial.print(this->sensor_name);
            Serial.println(" Attach");
=======
            bno055 = Adafruit_BNO055(55, 0x28);
            if (!bno055.begin())
            {
                Serial.print("No BNO055 detected");
                while (1)
                    ;
            }
            bno055.setExtCrystalUse(true);
            current_heading = 0;
>>>>>>> 01a00c663e643e510655256f5849c00e897c803e
        }

        void BNO055Compass::Update()
        {
<<<<<<< HEAD
            acc = imu.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
            gyr = imu.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
            mag = imu.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);

            current_heading = atan2(mag.y(),mag.x());
            Serial.print(this->sensor_name);
            Serial.println(" Update");
=======
            acc = bno055.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
            gyr = bno055.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
            mag = bno055.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);

            imu::Vector<3> euler = bno055.getVector(Adafruit_BNO055::VECTOR_EULER);

            current_heading = euler.x();
>>>>>>> 01a00c663e643e510655256f5849c00e897c803e
        }

        bool BNO055Compass::Calibrate()
        {
            uint8_t system, gyro, accel, mg = 0;
<<<<<<< HEAD
            imu.getCalibration(&system, &gyro, &accel, &mg);

            Serial.print(this->sensor_name);
            Serial.println(" Calibrate");
            if((system == 0)||(gyro == 0)||(accel==0)||(mg==0))
=======
            bno055.getCalibration(&system, &gyro, &accel, &mg);

            Serial.print(this->sensor_name);
            Serial.println(" Calibrate");
            if ((system == 0) || (gyro == 0) || (accel == 0) || (mg == 0))
>>>>>>> 01a00c663e643e510655256f5849c00e897c803e
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

<<<<<<< HEAD
        int BNO055Compass::getHeading()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Get Heading");
            return current_heading;
        }

=======
        double BNO055Compass::GetHeading() const
        {
            return current_heading;
        }

        std::tuple<double, double, double> BNO055Compass::GetAccelVector()
        {
            imu::Vector<3> accel = bno055.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);

            return std::make_tuple(accel[0], accel[1], accel[2]);
        }

>>>>>>> 01a00c663e643e510655256f5849c00e897c803e

    }  // namespace compass

}  // namespace sensor
