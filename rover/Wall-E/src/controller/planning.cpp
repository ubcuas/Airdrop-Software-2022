#include "controller/planning.h"

namespace controller
{
    Planning::Planning()
    {
        final_arrived      = false;
        waypoints_created  = false;
        distance_threshold = estimation::INTERMEDIATE_WAYPOINT_THRESHOLD;
    }
    void Planning::CreateWaypoint(std::pair<double, double> src)
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

    std::pair<double, double> Planning::UpdateWaypoint(std::pair<double, double> src)
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

}  // namespace controller