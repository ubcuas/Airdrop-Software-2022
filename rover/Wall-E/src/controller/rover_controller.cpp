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
    double RoverController::HeadingController(std::pair<double, double> src, std::pair<double, double> dest)
    {
        double turn_angle = sensor::gps::GPSCoordinate::CourseTo(src.first, src.second, dest.first, dest.second);
        while (turn_angle > 180)
        {
            turn_angle -= 360;
        }
        while (turn_angle < -180) 
        {
            turn_angle += 360;
        }
        return turn_angle;
    }

    void RoverController::LandingDetectionUpdate()
    {

    }
            
    bool RoverController::GetLandingStatus()
    {
        return true;
    }

    bool RoverController::ReachedWaypoint(std::pair<double, double> src, std::pair<double, double> dest, double distance_threshold)
    {
        return sensor::gps::GPSCoordinate::DistanceBetween(src.first, src.second, dest.first, dest.second) <= distance_threshold;
    }
}  // namespace controller
