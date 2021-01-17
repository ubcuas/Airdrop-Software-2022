#include "controller/planning.h"

namespace controller
{
    Planning::Planning()
    {
        final_arrived      = false;
        waypoints_created  = false;
        distance_threshold = estimation::INTERMEDIATE_WAYPOINT_THRESHOLD;
    }
    void Planning::CreateWaypoint(std::pair<double, double> current_coordinate)
    {
        if (!waypoints_created)
        {
            double distance = sensor::gps::GPSCoordinate::DistanceBetween(
                current_coordinate.first, current_coordinate.second,
                FINAL_WAYPOINT.GetLatitude(), FINAL_WAYPOINT.GetLongitude());

            Serial.printf("===================????????????????????? \n", distance);
            sensor::gps::GPSCoordinate current_location = sensor::gps::GPSCoordinate(
                current_coordinate.first, current_coordinate.second);

            double increment = distance / estimation::WAYPOINT_NUMBER;

            // create the waypoint map
            // for (double bearing = increment; bearing < distance; bearing += increment)
            // {
            //     auto waypoint = sensor::gps::GPSCoordinate::GetIntermediatePoint(
            //         current_location, FINAL_WAYPOINT, increment);
            //     intermediate_waypoints.push(
            //         sensor::gps::GPSCoordinate(waypoint.first, waypoint.second));
            // }
            intermediate_waypoints.push(sensor::gps::GPSCoordinate(
                estimation::DEFAULT_FINAL_LATITUDE, estimation::DEFAULT_FINAL_LONGITUDE));

            waypoints_created = true;
        }
    }

    std::pair<double, double> Planning::UpdateWaypoint(
        std::pair<double, double> current_coordinate)
    {
        sensor::gps::GPSCoordinate next_waypoint = (intermediate_waypoints.size() > 0)
                                                       ? intermediate_waypoints.front()
                                                       : FINAL_WAYPOINT;
        if (sensor::gps::GPSCoordinate::DistanceBetween(
                current_coordinate.first, current_coordinate.second,
                next_waypoint.GetLatitude(),
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
                // update a new waypoint
                next_waypoint = intermediate_waypoints.front();
                return std::make_pair(next_waypoint.GetLatitude(),
                                      next_waypoint.GetLongitude());
            }
        }
        else
        {
            // keep going at the current waypoint
            return std::make_pair(next_waypoint.GetLatitude(),
                                  next_waypoint.GetLongitude());
        }
    }

    std::pair<double, double> Planning::GetNextWayPoint()
    {
        sensor::gps::GPSCoordinate next_waypoint = intermediate_waypoints.front();
        return std::make_pair(next_waypoint.GetLatitude(), next_waypoint.GetLongitude());
    }
}  // namespace controller