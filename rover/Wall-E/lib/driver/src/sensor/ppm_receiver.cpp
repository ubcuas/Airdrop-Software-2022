#include <PulsePosition.h>
#include <pin_assignment.h>
#include <sensor/ppm_receiver.h>

PulsePositionInput ppm_input;
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
            ppm_input.begin(pin::RC_INPUT);
        }

        void PPMReceiver::Update()
        {
            throttle_channel = ppm_input.read(3);
            yaw_channel      = ppm_input.read(4);
        }

        bool PPMReceiver::Calibrate()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Calibrate");
            return false;
        }

        void PPMReceiver::Debug()
        {
            Serial.println("PPM RC ==================");
            Serial.println(throttle_channel);
            Serial.println(yaw_channel);
            Serial.println("===================");
        }
    }  // namespace rc

}  // namespace sensor
