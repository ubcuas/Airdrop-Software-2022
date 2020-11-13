#include <sensor/ppm_receiver.h>

namespace sensor
{
    namespace rc
    {
        bool PPMReceiver::CheckConnection()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Checking Connection");
            return false;
        }

        void PPMReceiver::Attach()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Attach");
        }

        void PPMReceiver::Update()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Update");
        }

        bool PPMReceiver::Calibrate()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Calibrate");
            return false;
        }

        void PPMReceiver::Debug()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Debug");
        }
    }  // namespace rc

}  // namespace sensor
