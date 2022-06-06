#include "Winch_Libraries.h"
#include "Pin_Assignments.h"
#include "Magnetic_Encoder.h"

// Datasheet: https://docs.broadcom.com/doc/AV02-0188EN

double read_time_uS = 0;

/*
 * Purpose: Set pin modes, intitialize values
 * Input: encoder_data object
 */
void encoderSetup(struct encoder_data * feedback_data) {
  pinMode(ENC_CSN, OUTPUT);
  pinMode(ENC_CLK, OUTPUT);
  pinMode(ENC_DO, INPUT);

  // Let's start here
  digitalWrite(ENC_CLK, HIGH);
  digitalWrite(ENC_CSN, HIGH);

  feedback_data->position_m = 0;
  feedback_data->prev_state = readEncSensor();
  feedback_data->rotary_state = 0;

  read_time_uS = micros();
}

/*
 * Purpose: read encoder data
 * Output: position of encoder
 */
unsigned int readEncSensor(){
  unsigned int data_out = 0;

  digitalWrite(ENC_CSN, LOW);
  delayMicroseconds(1); // Waiting for Tclkfe

  // Passing 12 times, from 0 to 11
  for (int x = 0; x < 12; x++) {
    digitalWrite(ENC_CLK, LOW);
    delayMicroseconds(1); // Tclk/2
    digitalWrite(ENC_CLK, HIGH);
    delayMicroseconds(1); // Tdo valid, like Tclk/2
    data_out = (data_out << 1) | digitalRead(ENC_DO); // Shift all the entering data to the left and pass the pin state to it; 1e bit is MSB (most significant bit)
  }

  digitalWrite(ENC_CSN, HIGH); // Deselects the encoder from reading
  //Serial.println(data_out);

  return data_out;
}

/*
 * Purpose: calculate and update encoder data
 * Input: encoder_data object
 */
void calcEncData (struct encoder_data * feedback_data) {
  unsigned int current_pos = readEncSensor();
  unsigned long prev_pos = feedback_data->prev_state;
  int current_rote = feedback_data->rotary_state;
  int delta_pos;  

  // At least one whole rotation CW (arbitrary designation)
  // 2000 was probably chosen because the raw data from encoder goes from 0-4096 - it goes back to zero after reaching 4096, so the difference between current and prev reading would be around 2000
  if (((int)current_pos-(int)prev_pos) < -2000){
    current_rote += 1;
    delta_pos = feedback_data->states_per_turn - (int)prev_pos + (int)current_pos;
  }
  // At least one whole rotation CCW
  else if (((int)current_pos-(int)prev_pos) > 2000) {
    current_rote -= 1;
    delta_pos = (int)current_pos - feedback_data->states_per_turn - (int)prev_pos;
  }
  // Partial rotation
  else {
    delta_pos = (int)current_pos - (int)prev_pos;
  }

  double current_time_uS = micros();
  double time_step_uS = (current_time_uS - read_time_uS);

  /*Serial.print("Current rotation: ");
  Serial.print(current_rote);
  Serial.print(" | ");
  Serial.print("Speed (rps): ");
  Serial.print(feedback_data->speed_rps);
  Serial.print(" | ");
  Serial.print("Current encoder position: ");
  Serial.print(current_pos);
  Serial.print(" | ");
  Serial.print("Height? (m): ");
  Serial.println(feedback_data->position_m*100, 3);*/

  // Update data
  feedback_data->speed_rps = ((delta_pos * 1000000.0) / ((feedback_data->states_per_turn) * time_step_uS));
  feedback_data->speed_mps = (feedback_data->speed_rps) * 2 * PI * (feedback_data->drum_radius_m);
  feedback_data->position_m = (feedback_data->position_m) + ((feedback_data->speed_mps) * time_step_uS / 1000000.0);
  
  feedback_data->prev_state = current_pos;
  feedback_data->rotary_state = current_rote;
  read_time_uS = current_time_uS;
}
