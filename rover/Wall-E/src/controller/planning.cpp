#include "controller/planning.h"

#include <constants.h>
#include <sensor/adafruit_ultimate_gps.h>
#include <sensor/gps_coordinate.h>

#include <list>

namespace controller
{
    std::list<double> pastLongitudes;
    std::list<double> pastLatitudes;
    double currentSumLongitudes;
    double currentSumLattitudes;

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

    bool Planning::CheckStability(std::pair<double, double> src)
    {
        pastLongitudes.push_front(src.first);
        pastLatitudes.push_front(src.second);
        
        if(pastLatitudes.size() > magic::NUM_DATA_POINTS){
            pastLatitudes.pop_back();
            pastLongitudes.pop_back();
        }

        std::pair<double, double> averageDeviation = AverageDeviation();

        if(averageDeviation.first < magic::MAX_DEVIATION && averageDeviation.second < magic::MAX_DEVIATION){
            return true;
        }else{
            return false;
        }
    }

    std::pair<double, double> Planning::AverageDeviation()
    {
        double meanLatitude  = 0;
        double meanLongitude = 0;
        double sumLongitude = 0;
        double sumLatitude = 0;
        double averageDeviationLatitude = 0;
        double averageDeviationLongitude = 0;

        for (std::list<double>::const_iterator iterator = pastLongitudes.begin(),
                                               end      = pastLongitudes.end();
             iterator != end; ++iterator)
        {
            sumLongitude += *iterator;
        }

        for (std::list<double>::const_iterator iterator = pastLatitudes.begin(),
                                               end      = pastLatitudes.end();
             iterator != end; ++iterator)
        {
            sumLatitude += *iterator;
        }

        meanLongitude = sumLongitude/pastLongitudes.size();
        meanLatitude = sumLatitude/pastLatitudes.size();

        for (std::list<double>::const_iterator iterator = pastLongitudes.begin(),
                                               end      = pastLongitudes.end();
             iterator != end; ++iterator)
        {
            averageDeviationLongitude += abs(*iterator - meanLongitude);
            averageDeviationLongitude = averageDeviationLongitude/pastLongitudes.size();
        }

        for (std::list<double>::const_iterator iterator = pastLatitudes.begin(),
                                               end      = pastLatitudes.end();
             iterator != end; ++iterator)
        {
            averageDeviationLatitude += abs(*iterator - meanLatitude);
            averageDeviationLatitude = averageDeviationLatitude/pastLatitudes.size();
        }

        return std::make_pair(averageDeviationLatitude,averageDeviationLongitude);
    }
}  // namespace controller