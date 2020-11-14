#pragma once
#include <actuator/actuator.h>
namespace actuator
{
    namespace motor
    {
        enum class MotorMapping
        {
            LEFT_MOTOR,
            RIGHT_MOTOR
        };
        class DCMotor : public actuator::Actuator
        {
           private:
            double current_velocity;
            uint8_t pwm_pin;
            uint8_t dir_a_pin;
            uint8_t dir_b_pin;

           public:
            DCMotor(String actuator_name, MotorMapping motor_location);

            virtual bool CheckConnection() override;

            virtual void Attach() override;

            virtual void Update() override;

            virtual void Debug() override;
            /**
             * @brief Motor's input function that takes 100 to -100 precent to change the
             * speed of motor. The direction of left motor and right motor must be
             * according to the compass coordinate.
             *
             * Note that change input will not directly change the input of the motor
             * @param input -100 to 100
             */
            virtual void ChangeInput(int input) override;

            void ReverseMotor();

            double GetVelocity() const;

            void StopMotor();
        };
    }  // namespace motor
}  // namespace actuator