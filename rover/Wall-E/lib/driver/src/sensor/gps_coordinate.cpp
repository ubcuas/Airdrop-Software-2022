#include <TinyGPS++.h>
#include <sensor/gps_coordinate.h>
namespace sensor
{
    namespace gps
    {
        GPSCoordinate::GPSCoordinate(float lat, float longi)
        {
            this->latitude  = lat;
            this->longitude = longi;
        }

        void GPSCoordinate::SetLatitude(float lat)
        {
            this->latitude = lat;
        }
        void GPSCoordinate::SetLongitude(float longi)
        {
            this->longitude = longi;
        }

        float GPSCoordinate::GetLatitude() const
        {
            return this->latitude;
        }

        float GPSCoordinate::GetLongitude() const
        {
            return this->longitude;
        }


        float GPSCoordinate::GetDistanceBetween(GPSCoordinate src, GPSCoordinate dest)
        {
            return sensor::gps::GPSCoordinate::DistanceBetween(
                src.GetLatitude(), src.GetLongitude(), dest.GetLatitude(),
                dest.GetLongitude());
            ;
        }

        float GPSCoordinate::GetHeadingBetween(GPSCoordinate src, GPSCoordinate dest)
        {
            return sensor::gps::GPSCoordinate::CourseTo(
                src.GetLatitude(), src.GetLongitude(), dest.GetLatitude(),
                dest.GetLongitude());
            ;
        }

        float GPSCoordinate::DistanceBetween(float lat1, float long1, float lat2,
                                             float long2)
        {
            return TinyGPSPlus::distanceBetween(lat1, long1, lat2, long2);
        }
        float GPSCoordinate::CourseTo(float lat1, float long1, float lat2, float long2)
        {
            return TinyGPSPlus::courseTo(lat1, long1, lat2, long2);
        }


        std::pair<float, float> GPSCoordinate::GetIntermediatePoint(GPSCoordinate src,
                                                                    GPSCoordinate dest,
                                                                    float distance)
        {
            float f = distance / sensor::gps::GPSCoordinate::DistanceBetween(
                                     src.GetLatitude(), src.GetLongitude(),
                                     dest.GetLatitude(), dest.GetLongitude());
            float delta = distance / 6372795;  // m
            float a     = sin((1 - f) * delta) / sin(delta);
            float b     = sin(f * delta) / sin(delta);
            float x     = a * cos(src.GetLatitude()) * cos(src.GetLongitude()) +
                      b * cos(dest.GetLatitude()) * cos(dest.GetLongitude());
            float y = a * cos(src.GetLatitude()) * sin(src.GetLongitude()) +
                      b * cos(dest.GetLatitude()) * sin(dest.GetLongitude());
            float z        = a * cos(src.GetLatitude()) + b * cos(dest.GetLatitude());
            float theta_i  = atan2(z, sqrt(pow(x, 2) + pow(y, 2)));
            float lambda_i = atan2(y, x);
            return std::make_pair(theta_i, lambda_i);
        }
        std::pair<float, float> GPSCoordinate::ConvertToPair() const
        {
            return std::make_pair(GPSCoordinate::GetLatitude(),
                                  GPSCoordinate::GetLongitude());
        }
        GPSCoordinate GPSCoordinate::CovertFromPair(std::pair<double, double> src)
        {
            return GPSCoordinate(src.first, src.second);
        }

    }  // namespace gps
}  // namespace sensor