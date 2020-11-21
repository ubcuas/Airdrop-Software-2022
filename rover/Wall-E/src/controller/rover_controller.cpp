#include "controller/rover_controller.h"

namespace controller
{
    RoverController::RoverController() {}
    std::pair<double, double> RoverController::MotorController(int throttle, int turn_angle)
    {
        return std::make_pair(0, 0);
    }
    std::pair<double, double> RoverController::RCController(int throttle_value, int yaw_value)
    {
        return std::make_pair(0, 0);
    }
    std::pair<double, double> RoverController::AutoController(sensor::gps::GPSCoordinate src, sensor::gps::GPSCoordinate dest)
    {
        double throttle = 100;
        double turn_angle{HeadingController(src, dest)};

        return std::make_pair(throttle, turn_angle);
    }
}  // namespace controller
