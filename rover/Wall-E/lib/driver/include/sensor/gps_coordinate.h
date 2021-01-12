#pragma once

#include <sensor/sensor.h>

namespace sensor
{
    namespace gps
    {
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
            float GetDistance(GPSCoordinate dest);
            float GetHeading(GPSCoordinate dest);
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
            static std::pair<float, float> GetIntermediatePoint(GPSCoordinate src, GPSCoordinate dest, float distance);
            std::pair<float, float> ConvertToPair() const;
        };
    }  // namespace gps

}  // namespace sensor
