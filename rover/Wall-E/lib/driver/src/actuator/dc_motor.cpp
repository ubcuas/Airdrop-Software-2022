#include <actuator/dc_motor.h>
#include <pin_assignment.h>

namespace actuator
{
    namespace motor
    {
        DCMotor::DCMotor(String actuator_name, MotorMapping motor_location)
            : Actuator::Actuator(actuator_name)
        {
            this->connected        = false;
            this->current_velocity = 0;

            if (motor_location == MotorMapping::LEFT_MOTOR)
            {
                this->pwm_pin   = pin::MOTOR_L_PWM;
                this->dir_a_pin = pin::MOTOR_L_DIR_A;
                this->dir_b_pin = pin::MOTOR_L_DIR_B;
            }
            else
            {
                this->pwm_pin   = pin::MOTOR_R_PWM;
                this->dir_a_pin = pin::MOTOR_R_DIR_A;
                this->dir_b_pin = pin::MOTOR_R_DIR_B;
            }
        }

        bool DCMotor::CheckConnection()
        {
            // More of a dummy function. Without encoder, there is no way to check if the connection
            // is established
            return connected;
        }

        void DCMotor::Attach()
        {
            pinMode(this->pwm_pin, OUTPUT);
            pinMode(this->dir_a_pin, OUTPUT);
            pinMode(this->dir_b_pin, OUTPUT);
            this->connected = true;
        }

        void DCMotor::Update()
        {
            if (this->current_velocity > 0)
            {
                digitalWrite(this->dir_a_pin, LOW);
                digitalWrite(this->dir_b_pin, HIGH);
            }
            else
            {
                digitalWrite(this->dir_a_pin, HIGH);
                digitalWrite(this->dir_b_pin, LOW);
            }
            analogWrite(this->pwm_pin, map(abs(this->current_velocity), 0, 100, 0, 255));
        }

        void DCMotor::ChangeInput(int input)
        {
            this->current_velocity = input;
        }

        double DCMotor::GetVelocity() const
        {
            return this->current_velocity;
        }

        void DCMotor::StopMotor()
        {
            current_velocity = 0;
            digitalWrite(this->dir_a_pin, LOW);
            digitalWrite(this->dir_b_pin, LOW);
        }

        void DCMotor::Debug()
        {
            Serial.println("motor debug ===");
            Serial.print(this->actuator_name);
            Serial.print(": ");
            Serial.print(this->current_velocity);
            Serial.println(" m/s");
            Serial.println("============");
        }
    }  // namespace motor
}  // namespace actuator
