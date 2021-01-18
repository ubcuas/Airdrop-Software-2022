/**
 * @file pwm_receiver.h
 * @brief
 * @version 1.0
 * @date 2021-01-17
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once
#include <Arduino.h>
#include <sensor/rc_receiver.h>

namespace sensor
{
    namespace rc
    {
        class PWMReceiver : public RCReceiver
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
