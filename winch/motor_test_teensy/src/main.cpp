#include <Arduino.h>
#include <Servo.h>

#define REEL_MOTOR_PIN 5
#define MOTOR_STOP 1000
#define MOTOR_MAX 2000

#define BRAKE_SERVO_PIN 7
#define ACTUATOR_MAX 1000
#define ACTUATOR_MIN 2000

Servo motor;
Servo brake_servo;

void setup() {
  motor.attach(REEL_MOTOR_PIN);
  motor.writeMicroseconds(MOTOR_STOP);
  delay(1000);
  motor.writeMicroseconds(MOTOR_MAX);
  delay(1000);

  brake_servo.attach(BRAKE_SERVO_PIN);
}

void loop() {
  motor.writeMicroseconds(MOTOR_STOP);
  delay(1000);
  motor.writeMicroseconds(MOTOR_MAX);
  delay(1000);

  brake_servo.writeMicroseconds(ACTUATOR_MAX);
  delay(1000);
  brake_servo.writeMicroseconds(ACTUATOR_MIN);
  delay(1000);
}