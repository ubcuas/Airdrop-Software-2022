#include <constants.h>
#include <pin_assignment.h>
#include <sensor/pwm_receiver.h>

namespace sensor
{
    namespace rc
    {
        void PWMReceiver::Attach()
        {
            pinMode(pin::THROTTLE_PIN, INPUT);
            pinMode(pin::YAW_PIN, INPUT);
            pinMode(pin::SWITCH_PIN, INPUT);
        }

        void PWMReceiver::Update()
        {
            this->throttle_channel_value =
                pulseIn(pin::THROTTLE_PIN, HIGH, magic::HIGH_READING);
            this->yaw_channel_value = pulseIn(pin::YAW_PIN, HIGH, magic::HIGH_READING);
            this->switch_channel_value =
                pulseIn(pin::SWITCH_PIN, HIGH, magic::HIGH_READING);
        }

        bool PWMReceiver::CheckConnection()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Checking Connection");
            return false;
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
            Serial.print(this->sensor_name);
            Serial.println(" Debug");
            Serial.println("PWM Sensor");
            Serial.print("Value Trottle = ");
            Serial.println(throttle_channel_value);
            Serial.print("Value Yaw = ");
            Serial.println(yaw_channel_value);
            Serial.print("Value SwitchMode = ");
            Serial.println(switch_channel_value);
            Serial.println(" ");
            delay(100);
        }  // namespace rc

    }  // namespace rc
}  // namespace sensor
