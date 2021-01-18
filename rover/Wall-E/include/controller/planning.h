/**
 * @file planning.h
 * @brief
 * @version 1.0
 * @date 2021-01-17
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once
#include <constants.h>
#include <sensor/gps_coordinate.h>

#include <queue>
namespace controller
{
    /**
     * @brief All GPS planning related code
     *
     */
    class Planning
    {
       private:
        bool waypoints_created;
        sensor::gps::GPSCoordinate FINAL_WAYPOINT = sensor::gps::GPSCoordinate(
            estimation::DEFAULT_FINAL_LATITUDE, estimation::DEFAULT_FINAL_LONGITUDE);

        std::queue<sensor::gps::GPSCoordinate> intermediate_waypoints;

        double distance_threshold;

       public:
        bool final_arrived;

        Planning();
        bool FinalArrived() const;

        /**
         * @brief Create a Waypoint object
         *
         * @param src
         */
        void CreateWaypoint(std::pair<double, double> src);

        /**
         * @brief refresh the way point array.
         *
         * @param src
         * @return std::pair<double, double>
         */
        std::pair<double, double> UpdateWaypoint(std::pair<double, double> src);

        /**
         * @brief Get the Next Way Point
         *
         * @return std::pair<double, double>  the next way point
         */
        std::pair<double, double> GetNextWayPoint();

        /**
         * Determines if the rover is close enough to the target location
         * @param src the current rover coordinate
         * @param dest the target rover coordinate
         * @param distance_threshold the maximum allowable distance to be considered close
         * enough
         * @returns true if the distance between the coordinates is less than the
         * distance_threshold
         */
        static bool ReachedWaypoint(std::pair<double, double> src, std::pair<double, double> dest,
                                    double distance_threshold);
    };
}  // namespace controller