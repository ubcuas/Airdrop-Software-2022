#pragma once
#include <acuator/acuator.h>
namespace acuator
{
    namespace motor
    {   
        class DCMotor : acuator::Acuator
        {
        private:
            bool direction;
            double current_speed; 

        public:
            /**
             *  @Brief Initialize the DC motor object with all the required pins
             */
            DCMotor(String acuator_name);

            /**
             *  @Brief Check Connection to the Motor
             */
            bool CheckConnection(void);

            /**
             *  @Brief Initialize and Attach Pins to the Motor
             */
            void Attach(void);

            /**
             *  @Brief Change PWM Input to the Motor
             */
            void ChangeInput(int input); 
            
            /**
             *  @Brief Reverse the Motor Spin Direction
             */
            void ReverseMotor(void);

            /**
             *  @Brief Stop Motor from Spinning
             */
            void StopMotor(void);

        };
    }
}