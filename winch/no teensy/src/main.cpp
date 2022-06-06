#include <Arduino.h>

#include "Winch_Libraries.h"
#include "Pin_Assignments.h"
#include "Magnetic_Encoder.h"
#include "Operation.h"

#define SERVO_MAX 2000
#define SERVO_MIN 1000

int mode = 1; // Mode: 1 for hold, 2 for reel down, 3 for reel up

// Winch operation
double total_dist = 1 * 7.4; // Total distance that the winch must reel down (m) **********************
int brake_servo_pos;
long start_time, current_time; // For timing, after the winch reaches the bottom

// PID variables
double 
  input, output, setpoint,
  Kp = 80, 
  Ki = 700, 
  Kd = 0;

PID speed_control(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);
struct encoder_data enc_drum;
Servo brake_servo;
Servo reel_motor;

void setup() {
  Serial.begin(9600);

  // Turn PID on
  speed_control.SetMode(AUTOMATIC);
  speed_control.SetOutputLimits(0,1000);
  
  enc_drum.drum_radius_m = 17.5/2 *0.001;
  enc_drum.states_per_turn = 4096;

  encoderSetup(&enc_drum);
  brake_servo.attach(BRAKE_SERVO_PIN);
  
  // Set up reel motor
  reel_motor.attach(REEL_MOTOR_PIN);
  reel_motor.writeMicroseconds(SERVO_MIN);
  delay(10);
  reel_motor.writeMicroseconds(SERVO_MAX);
  delay(10);

  // Limit switch for testing
  pinMode(LIMIT_SWITCH_PIN, INPUT_PULLUP);

}

void loop() {
  //Serial.println(mode);
  //Serial.println(enc_drum.position_m);
  //Serial.println(digitalRead(LIMIT_SWITCH_PIN));

  if (mode == 1) { // Hold
    reel_motor.writeMicroseconds(SERVO_MIN); // Reel motor off
    brake_servo.writeMicroseconds(SERVO_MAX); // Max braking

    enc_drum.position_m = 0;

    // For testing; in actual operation, we will be receiving a signal from aircraft to start reeling down
    if (digitalRead(LIMIT_SWITCH_PIN) == LOW) {
      mode = 2;
      delay(1000);
    }
  }

  else if (mode == 2) { // Reel down
    calcEncData(&enc_drum);
    setpoint = calcTargetSpeed(total_dist, enc_drum.position_m);
    input = enc_drum.speed_mps;
    //Serial.print("Target speed: ");
    //Serial.println(setpoint);
    //Serial.println(input);
    //Serial.print("        ");
    //Serial.println(enc_drum.speed_mps);

    speed_control.Compute(); // Compute PID
    //Serial.print("Output to servo: ");
    //Serial.println(1500 - output);
    Serial.println(output);
    
    // Constrain output to range of servo
    brake_servo_pos = 2000 - output;
    if (brake_servo_pos > SERVO_MAX)
      brake_servo_pos = SERVO_MAX;
    else if (brake_servo_pos < SERVO_MIN)
      brake_servo_pos = SERVO_MIN;
    // Write to servo
    brake_servo.writeMicroseconds(brake_servo_pos);
    //Serial.println(brake_servo_pos);

    // When reaches bottom with 0.2 m error margin, start timer to wait for rover release ***********************
    if (total_dist - enc_drum.position_m > 1) { // Not at bottom yet
      start_time = millis();
    }
    else {
      current_time = millis(); // Start timer
    }

    if (current_time - start_time > 20 * 1000) { // After 10 seconds have elapsed *********************** 
      mode = 3;
      brake_servo.writeMicroseconds(SERVO_MIN); // Release brake
      delay(2000);
      start_time = current_time = millis(); // Reset timer
    }

    // For testing: if pressed, reel back up
    if (digitalRead(LIMIT_SWITCH_PIN) == LOW) {
      mode = 3;
      brake_servo.writeMicroseconds(SERVO_MIN); // Release brake
      delay(2000);
      start_time = current_time = millis(); // Reset timer
    }
  }

  else if (mode == 3) { // Reel up
    calcEncData(&enc_drum);
    brake_servo.writeMicroseconds(SERVO_MIN); // Release brake

    if (enc_drum.position_m > 0) { // 0.1 m error margin
      reel_motor.writeMicroseconds(1300); // Reel up
    }
    else {
      mode = 1;
    }

    // For testing: emergency stop switch
    if (digitalRead(LIMIT_SWITCH_PIN) == LOW) {
      mode = 1;
      delay(1000);
    }
  }
  
  delay(1);
  
}