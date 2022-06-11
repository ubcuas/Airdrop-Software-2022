#include <Arduino.h>

#include "Winch_Libraries.h"
#include "Pin_Assignments.h"
#include "Magnetic_Encoder.h"
#include "Operation.h"
#include "Communication.h"

#define SERVO_MAX 2000
#define SERVO_MIN 1000

int 
  mode = 1, // Mode: 1 for hold, 2 for reel down, 3 for reel up
  action = 0; // Signal to change mode

// Winch operation
double total_dist = 22.86; // Total distance that the winch must reel down 22.86 (m) *******************
int brake_servo_pos;
long start_time, current_time; // For timing, after the winch reaches the bottom

// PID variables ********************
double 
  input, output, setpoint,
  Kp = 50, //80
  Ki = 700,
  Kd = 20; //10

PID speed_control(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);
struct encoder_data enc_drum;
Servo brake_servo;
Servo reel_motor;

void setup() {
  Serial.begin(9600);

  // Turn PID on
  speed_control.SetMode(AUTOMATIC);
  speed_control.SetOutputLimits(0,1000);
  
  enc_drum.drum_radius_m = 18/2 *0.001;
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

  // LED for signal
  pinMode(LED_PIN, OUTPUT);

}

void loop() {
  Serial.println(mode);
  //Serial.println(enc_drum.position_m);

  action = readSerial(mode); // Read Serial input

  if (mode == 1) { // Hold
    reel_motor.writeMicroseconds(SERVO_MIN);  // Reel motor off
    brake_servo.writeMicroseconds(SERVO_MAX); // Max braking

    enc_drum.position_m = 0;

    // Switch input (for testing) or signal from odroid
    if (digitalRead(LIMIT_SWITCH_PIN) == LOW  ||  action == 1) {
      action = 0;   // Reset
      mode = 2;     // Change mode
      delay(1000);  // Wait so that button doesn't read twice
    }
  }

  else if (mode == 2) { // Reel down
    calcEncData(&enc_drum);
    setpoint = calcTargetSpeed(total_dist, enc_drum.position_m);
    input = enc_drum.speed_mps;
    //Serial.println(setpoint);
    //Serial.println(input);
    //Serial.println(enc_drum.speed_mps);

    speed_control.Compute(); // Compute PID
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

    // When reaches bottom with 20% error margin, start timer to wait for rover release ******************
    if (total_dist - enc_drum.position_m > total_dist * 0.2) { // Not near bottom yet
      start_time = millis();
    }
    else {
      current_time = millis();      // Near bottom, start timer
      digitalWrite(LED_PIN, HIGH);  // Turn on LED to signal timer start
    }

    // After 20 seconds have elapsed or switch pressed (for testing) or signal from odroid *******************
    if (current_time - start_time > (long)1000L * 20  ||  digitalRead(LIMIT_SWITCH_PIN) == LOW  ||  action == 1) {
      action = 0;                                   // Reset
      mode = 3;                                     // Change mode
      brake_servo.writeMicroseconds(SERVO_MIN);     // Release brake
      digitalWrite(LED_PIN, LOW);                   // Turn off LED
      delay(1500);                                  // Wait for servo
      start_time = current_time = millis();         // Reset timer
    }
  }

  else if (mode == 3) { // Reel up
    calcEncData(&enc_drum);
    current_time = millis(); // Timer
    brake_servo.writeMicroseconds(SERVO_MIN); // Keep brake released

    // If speed is pretty much zero (because it has reeled all the way back in and is stuck), stop reeling
    // Also add a 'more than 2 seconds have elapsed' requirement, since startup might be slow
    // Or if the encoder says we have reeled all the way back in
    if ( (enc_drum.speed_mps < 0.2  &&  (current_time - start_time) > (long)1000L * 2)  ||  (enc_drum.position_m <= 0) ) {
      //reel_motor.writeMicroseconds(SERVO_MIN);  // Reel motor off
      mode = 1;
      start_time = current_time = millis(); // Reset timer
      Serial.println("AIRDROPCOMPLETE");    // To odroid
    }
    // Otherwise, keep reeling up
    else {
      reel_motor.writeMicroseconds(1300);
    }

    // Switch pressed
    if (digitalRead(LIMIT_SWITCH_PIN) == LOW) {
      mode = 1;
      start_time = current_time = millis(); // Reset timer
      Serial.println("AIRDROPCOMPLETE");    // To odroid
      delay(1000);                          // Wait so that switch doesn't read twice
    }
  }
  
  delay(1);
  
}