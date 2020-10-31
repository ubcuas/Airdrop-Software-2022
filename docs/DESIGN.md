# Design

---

<!-- vscode-markdown-toc -->
* 1. [Software design](#Softwaredesign)
	* 1.1. [Diagram](#Diagram)
		* 1.1.1. [Sensor class](#Sensorclass)
		* 1.1.2. [Acuator class](#Acuatorclass)

<!-- vscode-markdown-toc-config
	numbering=true
	autoSave=true
	/vscode-markdown-toc-config -->
<!-- /vscode-markdown-toc -->



##  1. <a name='Softwaredesign'></a>Software design

###  1.1. <a name='Diagram'></a>Diagram

> We use [mermaid](https://docs.gitlab.com/ee/user/markdown.html#diagrams-and-flowcharts-using-mermaid) as our diagram generator.

####  1.1.1. <a name='Sensorclass'></a>Sensor class
```mermaid
classDiagram


class Sensor {
 <<interface>>
 +String sensor_name
 +bool connected
 +CheckConnection(): bool
 +Attach(): void
 +Update(): void
 +Calibrate(): bool
 +Stop(): bool
}

Sensor <|-- RCReceiver
RCReceiver *-- RCSwtichMode
class RCReceiver{
 <<interface>>
-int throttle_channel
-int yaw_channel
-int calibrated_throttle_max
-int calibrated_throttle_min
-int calibrated_yaw_max
-int calibrated_yaw_min
-int mode_thresh_terminate
-int mode_thresh_auto
-int mode_thresh_manual
+ReadThrottle(): int
+ReadYaw(): int
+ReadModeSwitch(): RCSwtichMode
}

class RCSwtichMode{
  <<enumeration>>
  TERMINATE
  AUTO
  MANUAL
}

RCReceiver <|-- PWMReceiver

RCReceiver <|-- PPMReceiver

Sensor <|-- BNO055
class BNO055 {
  -int current_heading
  +GetHeading(): int
}


Sensor <|-- GPS
class GPS {
  -TinyGPSPlus gps
  -GPSCoordinate current_gps
  +WaitForGPSConnection(): void
  +GetCurrentGPSCoordinate(): GPSCoordinate
}

GPS o-- GPSCoordinate
class GPSCoordinate {
  -double latitude
  -double longtitude
  +GPS(double lat, double longi)
  +GetDistanceTo(GPS dest): double
  +GetHeadingTo(GPS dest): double
  +GetDistanceBetween(GPS source, GPS dest): double
  +GetHeadingBetween(GPS source, GPS dest): double
}


Sensor <|-- Altimeter
class Altimeter {
  -double current_altitude
  +GetCurrentAltitude(): double
}

Sensor <|-- Encoder
class Encoder {
  -long current_tick
}


```

####  1.1.2. <a name='Acuatorclass'></a>Acuator class

```mermaid
classDiagram

class Acuator {
 <<interface>>
 +String acuator_name
 -bool connected
 +CheckConnection(): bool
 +Attach(): void
 +ChangeInput(int input): bool
}


Acuator <|-- Motor
class Motor {
  -bool direction
  -double current_speed
  -ReverseMotor(): void
}

Acuator <|-- Servo
class Servo {
  -int current_angle
  +GetCurrentAngle(): int
}
```
#### Controller class

```mermaid
classDiagram

class Mode {
    <<interface>>
    +Init(): void
    +Run(): void
    +Stop(): void
}

Mode <|-- ManualControlMode
Mode <|-- AutoMode
Mode <|-- LowPowerMode


StateMachine *-- State
class StateMachine {
    +StateMachine()
    +Init(): void
    +Run(): void
}
class Controller {
  +Controller()
  +MotorController(int throttle, int turn_angle): std::pair
  +ReadingPIDController(int heading): int
  +RCController(int throttle_value, int yaw_value): std::pair
}

class State {
  <<enumeration>>
  LPM
  DROP
  LANDED
  AUTO
  MANUAL
  TERMINATE
}
```
## Hardware design