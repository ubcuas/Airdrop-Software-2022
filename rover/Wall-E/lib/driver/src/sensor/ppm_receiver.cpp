
#include <PulsePosition.h>
#include <pin_assignment.h>
#include <sensor/ppm_receiver.h>

PulsePositionInput ppm_input;

namespace sensor
{
    namespace rc
    {
        void PPMReceiver::Attach()
        {
            ppm_input.begin(pin::RC_INPUT);
        }

        bool PPMReceiver::CheckConnection()
        {
            return false;
        }

        void PPMReceiver::Update()
        {
            throttle_channel_value = ppm_input.read(3);
            yaw_channel_value      = ppm_input.read(4);
            switch_channel_value   = ppm_input.read(5);
        }

        bool PPMReceiver::Calibrate()
        {
            return false;
        }

        void PPMReceiver::Debug()
        {
            Serial.println("RC=====================");
            Serial.println("PPM Sensor");
            Serial.print("Value Trottle = ");
            Serial.println(throttle_channel_value);
            Serial.print("Value Yaw = ");
            Serial.println(yaw_channel_value);
            Serial.print("Value SwitchMode = ");
            Serial.println(switch_channel_value);
            Serial.println("=================");
        }
    }  // namespace rc
}  // namespace sensor
