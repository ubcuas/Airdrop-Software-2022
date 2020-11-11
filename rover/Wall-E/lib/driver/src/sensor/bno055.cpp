#include <sensor/bno055.h>

namespace sensor
{
    namespace compass
    {
        bool BNO055Compass::CheckConnection()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Checking Connection");
            return false;
        }

        void BNO055Compass::Attach()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Attach");
        }

        void BNO055Compass::Update()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Update");
        }

        bool BNO055Compass::Calibrate()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Calibrate");
            return false;
        }

        void BNO055Compass::Debug()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Debug");
        }
    }  // namespace compass

}  // namespace sensor
