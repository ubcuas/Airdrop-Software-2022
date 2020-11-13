#pragma once
#include <acuator/acuator.h>
namespace acuator
{
    namespace motor
    {   
        class DCMotor : public acuator::Acuator
        {
        private:
            bool direction;
            double current_speed; 
            uint8_t pwm_pin;
            uint8_t dir_a_pin;
            uint8_t dir_b_pin;

        public:
            DCMotor(String motor_name, bool use_motor1);

            virtual bool CheckConnection(void) override;

            virtual void Attach(void) override;

            virtual void ChangeInput(int input) override; 
            
            void ReverseMotor(void);

            double GetSpeed(void);

            void StopMotor(void);

            bool GetDirection(void);
        };
    }
}