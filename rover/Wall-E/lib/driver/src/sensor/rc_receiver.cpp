#include <constants.h>
#include <pin_assignment.h>
#include <sensor/rc_receiver.h>

namespace sensor
{
    namespace rc
    {
        int RCReceiver::ReadThrottle()
        {
            return this->throttle_channel_value;
        }
        int RCReceiver::ReadYaw()
        {
            return this->yaw_channel_value;
        }

        RCSwitchMode RCReceiver::ReadRCSwitchMode()
        {
            if (this->switch_channel_value > magic::AUTO_MODE - magic::ERROR_MARGIN &&
                this->switch_channel_value < magic::AUTO_MODE + magic::ERROR_MARGIN)
            {
                return RCSwitchMode::AUTO;
            }
            else if (this->switch_channel_value >
                         magic::TERMINATE_SIGNAL - magic::ERROR_MARGIN &&
                     this->switch_channel_value <
                         magic::TERMINATE_SIGNAL + magic::ERROR_MARGIN)
            {
                return RCSwitchMode::TERMINATE;
            }
            else
            {
                return RCSwitchMode::MANUAL;
            }
        }
    }  // namespace rc
}  // namespace sensor
