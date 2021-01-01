#include "controller/rover_controller.h"

#include <constants.h>
#include <pin_assignment.h>


namespace controller
{
    RoverController::RoverController()
    {
        final_arrived     = false;
        waypoints_created = false;
        landed            = false;
        landing_status_state.resize(estimation::LANDING_DETECTION_HISTORY_LENGTH);
        distance_threshold = estimation::INTERMEDIATE_WAYPOINT_THRESHOLD;
    }

    void RoverController::CreateWaypoint(std::pair<double, double> src)
    {
        if (!waypoints_created)
        {
            double distance = sensor::gps::GPSCoordinate::DistanceBetween(
                src.first, src.second, FINAL_WAYPOINT.GetLatitude(),
                FINAL_WAYPOINT.GetLongitude());
            sensor::gps::GPSCoordinate current_location =
                sensor::gps::GPSCoordinate(src.first, src.second);
            double increment = distance / estimation::WAYPOINT_NUMBER;
            for (double bearing = 0; bearing < distance; bearing += increment)
            {
                auto waypoint = sensor::gps::GPSCoordinate::GetIntermediatePoint(
                    current_location, FINAL_WAYPOINT, bearing);
                intermediate_waypoints.push(
                    sensor::gps::GPSCoordinate(waypoint.first, waypoint.second));
            }
            intermediate_waypoints.push(sensor::gps::GPSCoordinate(
                estimation::DEFAULT_FINAL_LATITUDE, estimation::DEFAULT_FINAL_LONGITUDE));
        }
    }
    bool RoverController::FinalArrived() const
    {
        return final_arrived;
    }

    std::pair<double, double> RoverController::UpdateWaypoint(
        std::pair<double, double> src)
    {
        sensor::gps::GPSCoordinate next_waypoint = (intermediate_waypoints.size() > 0)
                                                       ? intermediate_waypoints.front()
                                                       : FINAL_WAYPOINT;
        if (sensor::gps::GPSCoordinate::DistanceBetween(
                src.first, src.second, next_waypoint.GetLatitude(),
                next_waypoint.GetLongitude()) <= distance_threshold)
        {
            if (intermediate_waypoints.empty())
            {
                // the waypoint map is empty, thus we have arrived at the final waypoint.
                final_arrived = true;
                return std::make_pair(0, 0);
            }
            else
            {
                // remove the next waypoint
                intermediate_waypoints.pop();
                if (intermediate_waypoints.empty())
                {
                    // the next point is the final way point
                    distance_threshold = estimation::FINAL_WAYPOINT_THRESHOLD;
                    return std::make_pair(FINAL_WAYPOINT.GetLatitude(),
                                          FINAL_WAYPOINT.GetLongitude());
                }
                else
                {
                    // update a new waypoint
                    next_waypoint = intermediate_waypoints.front();
                    return std::make_pair(next_waypoint.GetLatitude(),
                                          next_waypoint.GetLongitude());
                }
            }
        }
        else
        {
            // keep going at the current waypoint
            return std::make_pair(next_waypoint.GetLatitude(),
                                  next_waypoint.GetLongitude());
        }
    }

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
    std::pair<double, double> RoverController::AutoController(
        std::pair<double, double> src, std::pair<double, double> dest)
    {
        double throttle = 100;
        double turn_angle{HeadingController(src, dest)};

        return std::make_pair(throttle, turn_angle);
    }

    double RoverController::HeadingController(std::pair<double, double> src,
                                              std::pair<double, double> dest)
    {
        double turn_angle = sensor::gps::GPSCoordinate::CourseTo(src.first, src.second,
                                                                 dest.first, dest.second);

        return (turn_angle - 180);
    }

    void RoverController::LandingDetectionUpdate(double accelx, double accely,
                                                 double accelz)
    {
        if (landed)
        {
            return;
        }
        // add to the average
        if (WithinLimit(average.x(), accelx, estimation::LANDING_ACCEL_THRESH) &&
            WithinLimit(average.y(), accely, estimation::LANDING_ACCEL_THRESH) &&
            WithinLimit(average.z(), accelz, estimation::LANDING_ACCEL_THRESH))
        {
            landing_status_state.push_back(true);
        }
        else
        {
            landing_status_state.push_back(false);
        }
        landing_status_state.pop_front();

        // check if confirm landing
        int count = 0;
        for (bool val : landing_status_state)
        {
            if (val)
            {
                count += 1;
            }
        }

        if ((count / estimation::LANDING_DETECTION_HISTORY_LENGTH) >
            estimation::LANDING_STATUS_CONFIRM_THRESH)
        {
            landed = true;
        }
        else
        {
            // update average
            average[0] =
                (average[0] * (estimation::LANDING_DETECTION_HISTORY_LENGTH - 1) +
                 accelx) /
                estimation::LANDING_DETECTION_HISTORY_LENGTH;
            average[1] =
                (average[1] * (estimation::LANDING_DETECTION_HISTORY_LENGTH - 1) +
                 accely) /
                estimation::LANDING_DETECTION_HISTORY_LENGTH;
            average[2] =
                (average[2] * (estimation::LANDING_DETECTION_HISTORY_LENGTH - 1) +
                 accelz) /
                estimation::LANDING_DETECTION_HISTORY_LENGTH;
        }
    }

    bool RoverController::WithinLimit(double src, double val, double limit) const
    {
        return false;
    }
    bool RoverController::GetLandingStatus() const
    {
        return landed;
    }

}  // namespace controller
