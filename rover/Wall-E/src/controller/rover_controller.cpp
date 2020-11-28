#include "controller/rover_controller.h"

#include <constants.h>
#include <pin_assignment.h>


namespace controller
{
    RoverController::RoverController() {}

    std::pair<double, double> RoverController::MotorController(int throttle,
                                                               int turn_angle)
    {
        double left  = throttle;
        double right = throttle;

        if (abs(turn_angle) > estimation::MOTOR_TURN_MIN_THRESH)
        {
            left = throttle + ((turn_angle > 0) ? 1 : -1) *
                                  ((turn_angle > 0) ? estimation::FULL_POWER - throttle
                                                    : estimation::FULL_POWER + throttle) *
                                  abs(turn_angle) / estimation::FULL_ANGLE;
            right =
                throttle + ((turn_angle < 0) ? 1 : -1) *
                               ((turn_angle < 0) ? estimation::FULL_POWER - throttle
                                                 : estimation::FULL_POWER + throttle) *
                               abs(turn_angle) / estimation::FULL_ANGLE;
        }

        return std::make_pair(left, right);
    }

    std::pair<double, double> RoverController::RCController(int throttle_value,
                                                            int yaw_value)
    {
        // mapping input transmitter val to output motor val

        int mappedSpeed = (throttle_value - magic::LOW_READING) / magic::PERCENTAGE;

        int mappedAngle =
            ((yaw_value - magic::LOW_READING) / magic::NUM_DEGREES) - magic::DEGREE_RANGE;

        return std::make_pair(mappedSpeed, mappedAngle);
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

        return (turn_angle - 180);
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
