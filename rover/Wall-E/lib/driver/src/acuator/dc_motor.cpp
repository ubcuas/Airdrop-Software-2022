#include <pin_assignment.h>
#include <acuator/dc_motor.h>


namespace acuator
{
    namespace motor
    {
        DCMotor::DCMotor(String motor_name, bool use_motor1):Acuator::Acuator(motor_name)
        {
            this->direction = true;
            this->connected = true;
            this->current_speed = 0; 
            this->pwm_pin = use_motor1? (pin::MOTOR1_PWM):(pin::MOTOR2_PWM);
            this->dir_a_pin = use_motor1? (pin::MOTOR1_DIR_A):(pin::MOTOR2_DIR_A);
            this->dir_b_pin = use_motor1? (pin::MOTOR1_DIR_B):(pin::MOTOR2_DIR_B);
        }

        bool DCMotor::CheckConnection(void)
        {
            Serial.print(this->acuator_name);
            Serial.println(" Checking Connection");
            return connected;
        }

        void DCMotor::Attach()
        {
            pinMode(this->pwm_pin,OUTPUT);
            pinMode(this->dir_a_pin,OUTPUT);
            pinMode(this->dir_b_pin,OUTPUT);
            Serial.print(this->acuator_name);
            Serial.println(" Attach");
        }

        void DCMotor::ChangeInput(int input)
        {
            if(direction == true)
            {
                digitalWrite(this->dir_a_pin, LOW);
                digitalWrite(this->dir_b_pin, HIGH);
            }
            else
            {
                digitalWrite(this->dir_a_pin, HIGH);
                digitalWrite(this->dir_b_pin, LOW);
            }
            analogWrite(this->pwm_pin, input);
            //Change motor speed value according to the PWM input, to be implemented
            Serial.print(this->acuator_name);
            Serial.println(" Changing Input");
        }

        void DCMotor::ReverseMotor(void)
        {
            this->direction ^= true;
            Serial.print(this->acuator_name);
            Serial.println(" Reversing Direction");
        }

        double DCMotor::GetSpeed(void)
        {
            return this->current_speed;
            Serial.print(this->acuator_name);
            Serial.println(" Getting Current Speed = this->current_speed");
        }

        void DCMotor::StopMotor(void)
        {
            digitalWrite(this->dir_a_pin, LOW);
            digitalWrite(this->dir_b_pin, LOW);
            Serial.print(this->acuator_name);
            Serial.println(" Stopping Motor");
        }

        bool DCMotor::GetDirection(void)
        {
            return this->direction; 
            Serial.print(this->acuator_name);
            Serial.println(" Getting Direction = this->direction");
        }
    }
}
