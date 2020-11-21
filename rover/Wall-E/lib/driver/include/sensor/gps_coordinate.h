#pragma once

#include <sensor/sensor.h>

namespace sensor
{
    namespace gps
    {
        class GPSCoordinate
        {
           private:
            double latitude;
            double longitude;

           public:
            /**
             * @brief Creates a GPSCoordinate instance.
             *
             * @param lat latitude of the coordinate in decimal degrees
             * @param longi longitude of the coordinate in decimal degrees
             */
            GPSCoordinate(double lat, double longi);
            double GetLatitude() const;
            double GetLongitude() const;
            void SetLatitude(double lat);
            void SetLongitude(double longi);
            double GetDistance(GPSCoordinate dest);
            double GetHeading(GPSCoordinate dest);
            static double GetDistanceBetween(GPSCoordinate src, GPSCoordinate dest);
            static double GetHeadingBetween(GPSCoordinate src, GPSCoordinate dest);
            static double DistanceBetween(double lat1, double long1, double lat2, double long2);
            static double CourseTo(double lat1, double long1, double lat2, double long2);
        };
    }  // namespace gps

}  // namespace sensor
