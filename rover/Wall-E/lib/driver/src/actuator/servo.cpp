#include <PWMServo.h>
#include <actuator/servo.h>
#include <pin_assignment.h>

PWMServo uas_servo;

namespace actuator
{
    namespace servo
    {
        bool Servo::CheckConnection()
        {
            return false;
        }

        void Servo::Attach()
        {
            uas_servo.attach(pin::SERVO_PIN);
        }

        void Servo::Update()
        {
            uas_servo.write(current_angle);
        }

        void Servo::Debug()
        {
            Serial.println("Servo==============");
            Serial.print(current_angle);
            Serial.println("=================");
        }
        void Servo::ChangeInput(int input)
        {
            current_angle = input;
        }
        int Servo::GetCurrentAngle() const
        {
            return current_angle;
        }
    }  // namespace servo
}  // namespace actuator