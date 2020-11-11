#include <sensor/adafruit_ultimate_gps.h>

namespace sensor
{
    namespace gps
    {
        bool AdafruitUltimateGPS::CheckConnection()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Checking Connection");
            return false;
        }

        void AdafruitUltimateGPS::Attach()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Attach");
        }

        void AdafruitUltimateGPS::Update()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Update");
        }

        bool AdafruitUltimateGPS::Calibrate()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Calibrate");
            return false;
        }

        void AdafruitUltimateGPS::Debug()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Debug");
        }
    }  // namespace gps

}  // namespace sensor
