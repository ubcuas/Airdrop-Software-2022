#include <Wire.h>
#include <pin_assignment.h>
#include <sensor/bno055.h>

namespace sensor
{
    namespace compass
    {
        bool BNO055Compass::CheckConnection()
        {
            if (bno055.begin())
            {
                Serial.println(" Connected!");
                return true;
            }
            Serial.println(" Disconnected!");
            return false;
        }

        void BNO055Compass::Attach()
        {
            // Use Wire1 for BN055 since Wire1 doesn't work for BMP280
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
            acc = bno055.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
            gyr = bno055.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
            mag = bno055.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);

            imu::Vector<3> euler = bno055.getVector(Adafruit_BNO055::VECTOR_EULER);

            current_heading = euler.x();
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
            Serial.printf("[Compass] \n=================\n");
            Serial.printf("Current heading: %f\n", current_heading);
            imu::Vector<3> data = bno055.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
            Serial.printf("linear accel: x: %f, y: %f, z: %f\n", data[0], data[1], data[2]);
            data = bno055.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
            Serial.printf("orientation: x: %f, y: %f, z: %f\n", data[0], data[1], data[2]);
            data = bno055.getVector(Adafruit_BNO055::VECTOR_EULER);
            Serial.printf("euler: x: %f, y: %f, z: %f\n", data[0], data[1], data[2]);
            Serial.println("=================");
        }

        double BNO055Compass::GetHeading() const
        {
            return current_heading;
        }

        std::tuple<double, double, double> BNO055Compass::GetAccelVector()
        {
            imu::Vector<3> data = bno055.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);

            return std::make_tuple(data[0], data[1], data[2]);
        }

        std::tuple<double, double, double> BNO055Compass::GetOrientationAccelVector()
        {
            imu::Vector<3> data = bno055.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);

            return std::make_tuple(data[0], data[1], data[2]);
        }

        std::tuple<double, double, double> BNO055Compass::GetEulerVector()
        {
            imu::Vector<3> data = bno055.getVector(Adafruit_BNO055::VECTOR_EULER);

            return std::make_tuple(data[0], data[1], data[2]);
        }

    }  // namespace compass

}  // namespace sensor
