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

            uint8_t system, gyro, accel = 0;
            bno055.getCalibration(&system, &gyro, &accel, &compass_calibration);

            imu::Vector<3> euler = bno055.getVector(Adafruit_BNO055::VECTOR_EULER);

            current_heading = euler.x();

            if ((current_heading - magic::COMPASS_OFFSET) < 0)
            {
                current_heading = current_heading - magic::COMPASS_OFFSET + 360;
            }
            else if ((current_heading + magic::COMPASS_OFFSET) > 360)
            {
                current_heading = current_heading + magic::COMPASS_OFFSET - 360;
            }
            else
            {
                current_heading -= magic::COMPASS_OFFSET;
            }
            current_heading = (current_heading > 180) ? (current_heading - 180)
                                                      : (current_heading + 180);
        }

        bool BNO055Compass::Calibrate()
        {
            uint8_t system, gyro, accel, mg = 0;
            bno055.getCalibration(&system, &gyro, &accel, &compass_calibration);

            if ((system == 0) || (gyro == 0) || (accel == 0) ||
                (compass_calibration == 0))
            {
                return false;
            }
            return true;
        }

        void BNO055Compass::Debug()
        {
            Serial.printf("[Compass] \n=================\n");
            Serial.printf("calibrate: %d\n", compass_calibration);
            Serial.printf("Current heading: %f\n", current_heading);
            imu::Vector<3> data = bno055.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
            Serial.printf("linear accel: x: %f, y: %f, z: %f\n", data[0], data[1],
                          data[2]);
            data = bno055.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
            Serial.printf("orientation: x: %f, y: %f, z: %f\n", data[0], data[1],
                          data[2]);
            data = bno055.getVector(Adafruit_BNO055::VECTOR_EULER);
            Serial.printf("euler: x: %f, y: %f, z: %f\n", data[0], data[1], data[2]);
            Serial.println("=================");
        }

        double BNO055Compass::GetHeading() const
        {
            return current_heading;
        }

        imu::Vector<3> BNO055Compass::GetAccelVector()
        {
            return bno055.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
        }

        imu::Vector<3> BNO055Compass::GetOrientationAccelVector()
        {
            return bno055.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
        }

        imu::Vector<3> BNO055Compass::GetEulerVector()
        {
            return bno055.getVector(Adafruit_BNO055::VECTOR_EULER);
        }

    }  // namespace compass

}  // namespace sensor
