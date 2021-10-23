#include <Arduino.h>
#include <Servo.h>

#define REEL_MOTOR_PIN 5

Servo reelMotor;
int speed = 0;

void setup() {
  reelMotor.attach(REEL_MOTOR_PIN); 

  Serial.begin(9600);
  while (! Serial);  // waits for active connection between serial and PC
  Serial.println("Speed 0 to 180");
}

void loop() {
  if (Serial.available()) {
    speed = Serial.println();
  }
  if (speed >= 0  &&  speed <= 180) {
    reelMotor.write(speed);
  }
}

