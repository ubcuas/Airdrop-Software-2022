# Design

---

## Software design

### Diagram

> We use [mermaid](https://docs.gitlab.com/ee/user/markdown.html#diagrams-and-flowcharts-using-mermaid) as our diagram generator.

Sensor class
```mermaid
classDiagram


class Sensor {
 <<interface>>
 +String sensor_name
 +bool connected
 +CheckConnection()*: bool
 +Attach()$: void
 +Update(): void
 +Calibrate(): bool
 +Stop(): bool
}


RCReceiver *-- PWMReceiver
class RCReceiver {
  - PWMReceiver throttle
  - PWMReceiver yaw
  + int ReadThrottle()
  + int ReadYaw()
}

Sensor <|-- PWMReceiver
class PWMReceiver {
  -int pwm_value
  +int ReadRCValue()
}

Sensor <|-- PPMReceiver
class PPMReceiver {
  -int throttle_channel
  -int yaw_channel
  +int ReadThrottle()
  +int ReadYaw()
}

Sensor <|-- BNO055
class BNO055 {
  -int current_heading
  +int GetHeading()
}


Sensor <|-- GPS
class GPS {
  - TinyGPSPlus gps
  - GPSCoordinate current_gps
  + void WaitForGPSConnection()
  + GPSCoordinate GetCurrentGPSCoordinate()
}

GPS o-- GPSCoordinate
class GPSCoordinate {
  - double latitude
  - double longtitude
  + GPS(double lat, double longi)
  + double GetDistanceTo(GPS dest)
  + double GetHeadingTo(GPS dest)
  + double GetDistanceBetween(GPS source, GPS dest)$
  + double GetHeadingBetween(GPS source, GPS dest)$
}


Sensor <|-- Altimeter
class Altimeter {
  - double current_altitude
  + double GetCurrentAltitude()
}

Sensor <|-- Encoder
class Encoder {
  - long current_tick

}


```

Acuator class

```mermaid
classDiagram

class Acuator {
 <<interface>>
 +String acuator_name
 -bool connected
 bool CheckConnection()*
 bool Attach() *
 bool ChangeInput(int input)*
}


Acuator <|-- Motor
class Motor {
  - bool direction
  - double current_speed
  - void ReverseMotor()
}

Acuator <|-- Servo
class Servo {
  - int current_angle
  + int GetCurrentAngle()
}
```


<!-- ```mermaid
classDiagram
class BankAccount{
    +String owner
    +BigDecimal balance
    +deposit(amount) bool
    +withdrawl(amount)
}
class ManualControlMode {

}

class AutoMode{

}

class LowPowerMode {

}


class StateMachine {

}
class Controller {
  - Motor left_motor
  - Motor right_motor
  + std::pair MotorController(int throttle, int turn_angle)
  + int HeadingPIDController(int heading)
  + std::pair RCController()
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
``` -->
## Hardware design