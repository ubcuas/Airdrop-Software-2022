#include <Arduino.h>

#include "Winch_Libraries.h"
#include "Pin_Assignments.h"
#include "Magnetic_Encoder.h"
#include "Operation.h"
//#include "PID.h"

#define SERVO_MAX 2000
#define SERVO_MIN 1000

int mode = 2; // Mode: 1 for hold, 2 for reel down, 3 for reel up

// Winch operation
double
  total_dist = 1.0, // total distance that the winch must reel down (m)
  dist_reeled = 0;
int brake_servo_pos;
long start_time, current_time; // for timing, after the winch reaches the bottom

// PID variables
double 
  input, output, setpoint,
  Kp = 2, 
  Ki = 5, 
  Kd = 0;

PID speed_control(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

/*int32_t l_bound = 0;
int32_t u_bound = 20;
int32_t i_l_bound = -10;
int32_t i_u_bound = 10;*/

//struct control_array speed_PID_vals;
struct encoder_data enc_drum;

Servo brake_servo;
//PID speed_controller = PID(l_bound, u_bound, i_l_bound, i_u_bound, true);

Servo reel_motor;

void setup() {
  Serial.begin(115200);

  // Turn PID on
  speed_control.SetMode(AUTOMATIC);

  /*speed_controller.setConstants(1.0, 0.0, 0.0);
  speed_controller.begin(1000, 15000, 5, &speed_PID_vals);*/
  
  enc_drum.drum_radius_m = 7.5*0.001;
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
  pinMode(LIMIT_SWITCH_PIN, INPUT);

  start_time = current_time = millis();
}

void loop() {
  if (mode == 1) { // Hold
    reel_motor.writeMicroseconds(SERVO_MIN); // Reel motor off
    brake_servo.writeMicroseconds(SERVO_MIN); // Max braking

    // For testing; in actual operation, we will be receiving a signal from aircraft to start reeling down
    if (digitalRead(LIMIT_SWITCH_PIN) == HIGH)
      mode = 2;
  }

  else if (mode == 2) { // Reel down
    calcEncData(&enc_drum);
    setpoint = calcTargetSpeed(total_dist, enc_drum.position_m);
    input = enc_drum.speed_mps;

    speed_control.Compute(); // Compute PID
    Serial.println(output);
    
    // Constrain output to range of servo
    brake_servo_pos = 1500 - output;
    if (brake_servo_pos > SERVO_MAX)
      brake_servo_pos = SERVO_MAX;
    else if (brake_servo_pos < SERVO_MIN)
      brake_servo_pos = SERVO_MIN;
    // Write to servo
    //brake_servo.writeMicroseconds(brake_servo_pos);

    if (abs(setpoint - 0.0) > 0.1) // 0.1 m/s error margin
      start_time = millis();
    else
      current_time = millis();
    
    // Wait 20(?) seconds
    if ((current_time - start_time) > 20 * 1000)
      mode = 3;
  }

  else if (mode == 3) { // reel up
    brake_servo.writeMicroseconds(SERVO_MAX); // Release brake
    while (enc_drum.position_m > 0.1) { // 0.1 m error margin
      reel_motor.writeMicroseconds(SERVO_MAX); // Reel up as fast as possible
    }
    mode = 1;
  }
  
  /*speed_PID_vals.target_val = 1.5;
  speed_PID_vals.current_val = enc_drum.speed_mps;
  Serial.print("Speed (m/s): ");
  Serial.println(enc_drum.speed_mps, 6);
  Serial.print("Position (m): ");
  Serial.println(enc_drum.position_m, 6);
  Serial.print("Actuator out :");
  Serial.println(-1 * speed_PID_vals.return_val * 1000 / u_bound + 1000);
  brake_servo.writeMicroseconds(-1 * speed_PID_vals.return_val * 1000 / u_bound + 1000);*/
  
  delay(50);
  
}