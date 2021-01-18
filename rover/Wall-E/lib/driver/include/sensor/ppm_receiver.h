/**
 * @file ppm_receiver.h
 * @brief
 * @version 1.0
 * @date 2021-01-17
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <Arduino.h>
#include <sensor/rc_receiver.h>

namespace sensor
{
    namespace rc
    {
        class PPMReceiver : public RCReceiver
        {
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
