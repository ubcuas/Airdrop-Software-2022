#pragma once

#include <sensor/rc_receiver.h>
namespace sensor
{
    namespace rc
    {
        class PPMReceiver : public RCReceiver
        {
           private:
            

           public:
            using RCReceiver::RCReceiver;

            virtual bool CheckConnection() override;

            virtual void Attach() override;

            virtual void Update() override;

            virtual bool Calibrate() override;

            virtual void Debug() override;
        };
    }  // namespace rc

}  // namespace sensor
