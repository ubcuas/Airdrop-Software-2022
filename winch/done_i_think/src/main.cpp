#include <Arduino.h>

#include "Winch_Libraries.h"
#include "Pin_Assignments.h"
#include "Magnetic_Encoder.h"
#include "Operation.h"
#include "Communication.h"

#define SERVO_MAX 2000
#define SERVO_MIN 1000

int 
  mode = 1, // Mode: 1 for hold, 2 for reel down, 3 for reel up, 4 for emergency reel up
  action = 0; // Signal to change mode

// Winch operation
double 
  total_dist = 24.38, // Total distance that the winch must reel down (m); 80ft = 24.38m *******************
  reeling_error = total_dist * 0.2; // Difference in string length when reeling up and down due to the string wrapping differently around drum
int brake_servo_pos;
long start_time, current_time; // For timing, after the winch reaches the bottom

// PID variables ********************
double 
  input, output, setpoint,
  Kp = 25, //50
  Ki = 25, //75
  Kd = 5; //50

PID speed_control(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);
struct encoder_data enc_drum;
Servo brake_servo;
Servo reel_motor;

void setup() {
  Serial.begin(9600);

  // Turn PID on
  speed_control.SetMode(AUTOMATIC);
  speed_control.SetOutputLimits(0, 255);
  
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
  //Serial.println(mode);
  //Serial.println(enc_drum.position_m);

  action = readSerial(mode); // Read Serial input

  if (mode == 1) { // Hold
    reel_motor.writeMicroseconds(SERVO_MIN);  // Reel motor off
    brake_servo.writeMicroseconds(SERVO_MAX); // Max braking
    enc_drum.position_m = 0;

    // Reset the PID output to zero
    if (output > 0) {
      setpoint = 0;
      input = 1;
      speed_control.Compute();
    }
    else if (output < 0) {
      setpoint = 2;
      input = 1;
      speed_control.Compute();
    }

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
    speed_control.Compute(); // Compute PID
    
    brake_servo_pos = map(output, -500, 255, 2000, 1000);
    //brake_servo_pos = 2000 - output;

    // Constrain output to range of servo
    if (brake_servo_pos > SERVO_MAX)
      brake_servo_pos = SERVO_MAX;
    else if (brake_servo_pos < SERVO_MIN)
      brake_servo_pos = SERVO_MIN;

    // Write to servo
    brake_servo.writeMicroseconds(brake_servo_pos);
    
    //Serial.println(setpoint);
    //Serial.println(input);
    //Serial.println(enc_drum.speed_mps);
    //Serial.println(brake_servo_pos);
    //Serial.println(output);
    //Serial.println(brake_servo_pos);

    // When reaches bottom with 20% error margin, start timer to wait for rover release ******************
    if (total_dist - enc_drum.position_m > total_dist * 0.2) { // Not near bottom yet
      start_time = millis();
    }
    else {
      current_time = millis();      // Near bottom, start timer
      digitalWrite(LED_PIN, HIGH);  // Turn on LED to signal timer start
    }

    // After 30 seconds have elapsed OR switch pressed (for testing)
    if (current_time - start_time > (long)1000L * 30  ||  digitalRead(LIMIT_SWITCH_PIN) == LOW) {
      action = 0;                                   // Reset
      mode = 3;                                     // Change mode
      brake_servo.writeMicroseconds(SERVO_MIN);     // Release brake
      digitalWrite(LED_PIN, LOW);                   // Turn off LED
      delay(500);                                   // Wait for servo
      start_time = current_time = millis();         // Reset timer
    }

    // Emergency reel up
    if (action == 2) {
      action = 0;                                   // Reset
      mode = 4;                                     // Change mode
      brake_servo.writeMicroseconds(SERVO_MIN);     // Release brake
      digitalWrite(LED_PIN, LOW);                   // Turn off LED
      start_time = current_time = millis();         // Reset timer
    }
  }

  else if (mode == 3) { // Reel up
    calcEncData(&enc_drum);
    current_time = millis(); // Timer
    brake_servo.writeMicroseconds(SERVO_MIN); // Keep brake released
    //Serial.println(current_time - start_time);
    //Serial.println(enc_drum.speed_mps);

    // Rover is stuck on the hook, go back to mode 2 (reel down)
    // This is detected if the motor is stalling (it can't carry weight of rover) and it is not the hook is not 
    // getting stuck because of reeling error and 2 seconds have elapsed to allow the motor to start up
    if ((abs(enc_drum.speed_mps) < 0.01)  &&  (enc_drum.position_m > reeling_error) &&  ((current_time - start_time) > (long)1000L * 2)) {
      reel_motor.writeMicroseconds(SERVO_MIN);  // Reel motor off
      mode = 2;                                 // Try reeling down again
      start_time = current_time = millis();     // Reset timer
      Serial.println("AIRDROPERROR");           // To odroid
    }
    // Stop reeling...
    // ... If speed is pretty much zero, because it has reeled all the way back in and the hook is stuck; we know 
    // this because it is within the reeling error and 2 seconds have elapsed to allow the motor to start up
    // ... Or if the encoder says we have reeled all the way back in
    else if ( ((abs(enc_drum.speed_mps) < 0.01)  &&  ((current_time - start_time) > (long)1000L * 2))  ||  (enc_drum.position_m <= 0) ) {
      mode = 1;
      start_time = current_time = millis(); // Reset timer
      Serial.println("AIRDROPCOMPLETE");    // To odroid
    }
    // Otherwise, keep reeling up
    else {
      reel_motor.writeMicroseconds(1100);
    }

    // Switch pressed
    if (digitalRead(LIMIT_SWITCH_PIN) == LOW) {
      mode = 1;
      start_time = current_time = millis(); // Reset timer
      Serial.println("AIRDROPCOMPLETE");    // To odroid
      delay(1000);                          // Wait so that switch doesn't read twice
    }
  }

  else if (mode == 4) { // Emergency reel up with rover
    calcEncData(&enc_drum);
    if ( ((abs(enc_drum.speed_mps) < 0.01)  &&  ((current_time - start_time) > (long)1000L * 2))  ||  (enc_drum.position_m <= 0) ) {
      mode = 1;                             // Back to holding mode
      start_time = current_time = millis(); // Reset timer
    }
    // Otherwise, keep reeling up
    else {
      reel_motor.writeMicroseconds(1600); // Higher power
    }
  }
  
  delay(1);
  
}