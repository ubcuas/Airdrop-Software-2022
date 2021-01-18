
/**
 * @file servo.h
 * @brief
 * @version 1.0
 * @date 2021-01-17
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <actuator/actuator.h>

namespace actuator
{
    namespace servo
    {
        /**
         * @brief Servo driver class.
         *
         */
        class Servo : public Actuator
        {
           private:
            int current_angle;

           public:
            using Actuator::Actuator;

            virtual bool CheckConnection() override;

            virtual void Attach() override;

            virtual void Update() override;

            virtual void Debug() override;

            virtual void ChangeInput(int input) override;

            int GetCurrentAngle() const;
        };
    }  // namespace servo
}  // namespace actuator