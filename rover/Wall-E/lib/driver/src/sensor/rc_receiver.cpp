#include <sensor/rc_receiver.h>

namespace sensor
{
    namespace rc
    {
        int RCReceiver::ReadThrottle()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Read throttle");
            return -1;
        }
        int RCReceiver::ReadYaw()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Read Yaw");
            return -1;
        }
        RCSwitchMode RCReceiver::ReadRCSwitchMode()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Read Mode");
            return RCSwitchMode::TERMINATE;
        }
    }  // namespace rc

}  // namespace sensor
