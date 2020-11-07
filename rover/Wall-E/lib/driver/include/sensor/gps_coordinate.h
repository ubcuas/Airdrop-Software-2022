#pragma once
namespace sensor
{
    namespace gps
    {
        class GPSCoordinate
        {
           private:
            double latitude;
            double longtitude;

           public:
            GPSCoordinate(double lat, double longi);
            double GetDistance(GPSCoordinate dest);
            double GetHeading(GPSCoordinate dest);
            static double GetDistanceBetween(GPSCoordinate src, GPSCoordinate dest);
            static double GetHeadingBetween(GPSCoordinate src, GPSCoordinate dest);
        };
    }  // namespace gps

}  // namespace sensor
