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
    std::pair<double, double> RoverController::AutoController(std::pair<double, double> src, std::pair<double, double> dest)
    {
        double throttle = 100;
        double turn_angle{HeadingController(src, dest)};

        return std::make_pair(throttle, turn_angle);
    }
    bool RoverController::ReachedWaypoint(std::pair<double, double> src, std::pair<double, double> dest, double distance_threshold)
    {
        return sensor::gps::GPSCoordinate::DistanceBetween(src.first, src.second, dest.first, dest.second) <= distance_threshold;
    }
}  // namespace controller
