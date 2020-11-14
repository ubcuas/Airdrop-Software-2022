#include <PulsePosition.h>
#include <Encoder.h>
#include <Servo.h>

#define CLKPIN 4
#define DTPIN 5

#define RX_PIN 6

#define PLACEHOLDER 0

#define DRUM_INTERRUPT_TIMER 200000
#define PID_INTERRUPT_TIMER 600000

#define ENCODER_STATES_PER_TURN 80
#define DRUM_RADIUS_MM 7.5
#define ACTUATOR_EXT_MM 20

#define SPEED_KP -2.0
#define SPEED_KI -0.8 
#define SPEED_KD 0.0

#define SPEED_INTEGRATOR_ABSOLUTE_BOUND 10
#define SPEED_INTEGRAL_CLAMPING_OFFSET 2

#define ALT_KP 0.0
#define ALT_KI 0.0
#define ALT_KD 0.0

Encoder wireDrum (CLKPIN, DTPIN);
Encoder manualControl (8, 9);
//PulsePositionInput rxWire;
Servo brakeServo ;
IntervalTimer drumRead;
IntervalTimer runPID;

long drumPos = -999;
long prevPos, currentPos;
unsigned long RX_raw [12] = {PLACEHOLDER, PLACEHOLDER, PLACEHOLDER, PLACEHOLDER, PLACEHOLDER, PLACEHOLDER, PLACEHOLDER, PLACEHOLDER, PLACEHOLDER, PLACEHOLDER, PLACEHOLDER, PLACEHOLDER};
int brakeForce = 0;
int channelAmount = 12;

float timePerDrumRead, RPS, drumSpeed, payloadPos, 
      speedIntegral, currentSpeedOut, prevSpeedOut, 
      altiIntegral, currentAltiOut, prevAltiOut,
      PID_error, actuatorX;


void setup() {
  Serial.begin(115200);
  brakeServo.attach(7);

  prevPos = 0;
  timePerDrumRead = DRUM_INTERRUPT_TIMER;
  payloadPos = 0;

  speedIntegral = 0;
  currentSpeedOut = 0;
  

  pinMode(24, INPUT);
  pinMode(25, INPUT);
    
  wireDrum.write(0);
  manualControl.write(0);
  //rxWire.begin(RX_PIN);
  drumRead.begin(drumPosCalc, DRUM_INTERRUPT_TIMER);
  runPID.begin(PID_master, PID_INTERRUPT_TIMER);
}

void loop() {
  /*
  for (int channel = 1; channel <= channelAmount; ++channel) {
      RX_raw [channel - 1] = rxWire.read(channel);
  }
  */

   brakeForce = (actuatorX*1000.0/ACTUATOR_EXT_MM);

   if (brakeForce < 0)
    brakeForce = 0;
   else if (brakeForce > 1000)
    brakeForce = 1000;

   brakeServo.writeMicroseconds(1000 + brakeForce);
}

void PID_master() {

  if(digitalRead(24) == LOW){
    if(digitalRead(25) == LOW){
      actuatorX = ACTUATOR_EXT_MM;
      manualControl.write(0);
    }      
    else if(digitalRead(25) == HIGH)
      actuatorX = manualControl.read()/4;
  }
   else if(digitalRead(25) == LOW)
    actuatorX = 0;
   else if(digitalRead(25) == HIGH)
    actuatorX = speedPID(1.5, RPS);

    if (actuatorX < 0)
    actuatorX = 0;
   else if (actuatorX > ACTUATOR_EXT_MM)
    actuatorX = ACTUATOR_EXT_MM;

   Serial.print(RPS);
   Serial.print(",");
   Serial.print(payloadPos);
   Serial.print(",");
   Serial.print(digitalRead(24));
   Serial.print(",");
   Serial.println(digitalRead(25));


}

int speedPID (float desiredSpeed, float currentSpeed) {
  PID_error = desiredSpeed - currentSpeed;
  
  if (currentSpeedOut <= (0+SPEED_INTEGRAL_CLAMPING_OFFSET) || currentSpeedOut >= (ACTUATOR_EXT_MM-SPEED_INTEGRAL_CLAMPING_OFFSET))
    speedIntegral += 0;
  else
    speedIntegral += SPEED_KI * PID_error;

  if (speedIntegral > SPEED_INTEGRATOR_ABSOLUTE_BOUND)
    speedIntegral = SPEED_INTEGRATOR_ABSOLUTE_BOUND;
  else if (speedIntegral <= (-1*SPEED_INTEGRATOR_ABSOLUTE_BOUND))
    speedIntegral = (-1*SPEED_INTEGRATOR_ABSOLUTE_BOUND);
     
  currentSpeedOut = (SPEED_KP * PID_error) + speedIntegral;
  
  if (currentSpeedOut < 0)
    currentSpeedOut = 0;
  else if(currentSpeedOut > 20)
    currentSpeedOut = 20;
    
  return currentSpeedOut;
}

int posPID (float desiredAlti, float currentAlti) {
  PID_error = desiredAlti - currentAlti;
  altiIntegral += ALT_KI * PID_error;
  return ALT_KP * PID_error + altiIntegral;
}

void drumPosCalc() {
  currentPos = wireDrum.read();
  RPS = ((currentPos - prevPos)*1000000/(ENCODER_STATES_PER_TURN*timePerDrumRead));
  drumSpeed = RPS * 2 * PI * DRUM_RADIUS_MM*0.001 ;
  prevPos = currentPos;
  payloadPos += (RPS * timePerDrumRead * 2 * PI * DRUM_RADIUS_MM/(1000*1000000));
}