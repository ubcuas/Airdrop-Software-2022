#include <sensor/pwm_receiver.h>

namespace sensor
{
    namespace rc
    {
        bool PWMReceiver::CheckConnection()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Checking Connection");
            return false;
        }

        void PWMReceiver::Attach()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Attach");
        }

        void PWMReceiver::Update()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Update");
        }

        bool PWMReceiver::Calibrate()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Calibrate");
            return false;
        }

        void PWMReceiver::Debug()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Debug");
        }
    }  // namespace rc

}  // namespace sensor
