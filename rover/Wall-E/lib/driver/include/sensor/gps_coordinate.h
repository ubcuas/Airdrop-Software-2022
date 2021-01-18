/**
 * @file gps_coordinate.h
 * @brief
 * @version 1.0
 * @date 2021-01-17
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include <sensor/sensor.h>

namespace sensor
{
    namespace gps
    {
        /**
         * @brief Holds the GPS data.
         * TODO: redesign this. It's not well designed
         */
        class GPSCoordinate
        {
           private:
            float latitude;
            float longitude;

           public:
            /**
             * @brief Creates a GPSCoordinate instance.
             *
             * @param lat latitude of the coordinate in decimal degrees
             * @param longi longitude of the coordinate in decimal degrees
             */
            GPSCoordinate(float lat, float longi);
            float GetLatitude() const;
            float GetLongitude() const;
            void SetLatitude(float lat);
            void SetLongitude(float longi);

            static float GetDistanceBetween(GPSCoordinate src, GPSCoordinate dest);
            static float GetHeadingBetween(GPSCoordinate src, GPSCoordinate dest);
            static float DistanceBetween(float lat1, float long1, float lat2, float long2);
            static float CourseTo(float lat1, float long1, float lat2, float long2);

            /**
             * @brief Get the Intermediate Point object
             *  http://www.movable-type.co.uk/scripts/latlong.html
             * @param src
             * @param dest
             * @param distance
             * @return float
             */
            static std::pair<float, float> GetIntermediatePoint(GPSCoordinate src,
                                                                GPSCoordinate dest, float distance);
            std::pair<float, float> ConvertToPair() const;
            static GPSCoordinate CovertFromPair(std::pair<double, double> src);
        };
    }  // namespace gps

}  // namespace sensor
