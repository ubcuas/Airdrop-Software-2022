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

        float GPSCoordinate::GetDistance(GPSCoordinate dest)
        {
            float distance = GPSCoordinate::DistanceBetween(
                latitude, longitude, dest.latitude, dest.longitude);
            return distance;
        }

        float GPSCoordinate::GetHeading(GPSCoordinate dest)
        {
            float heading = GPSCoordinate::CourseTo(latitude, longitude, dest.latitude,
                                                     dest.longitude);
            return heading;
        }

        float GPSCoordinate::GetDistanceBetween(GPSCoordinate src, GPSCoordinate dest)
        {
            float distance =
                GPSCoordinate::DistanceBetween(src.GetLatitude(), src.GetLongitude(),
                                               dest.GetLatitude(), dest.GetLongitude());
            return distance;
        }

        float GPSCoordinate::GetHeadingBetween(GPSCoordinate src, GPSCoordinate dest)
        {
            float heading =
                GPSCoordinate::CourseTo(src.GetLatitude(), src.GetLongitude(),
                                        dest.GetLatitude(), dest.GetLongitude());
            return heading;
        }

        float GPSCoordinate::DistanceBetween(float lat1, float long1, float lat2,
                                              float long2)
        {
            float delta  = radians(long1 - long2);
            float sdlong = sin(delta);
            float cdlong = cos(delta);
            lat1          = radians(lat1);
            lat2          = radians(lat2);
            float slat1  = sin(lat1);
            float clat1  = cos(lat1);
            float slat2  = sin(lat2);
            float clat2  = cos(lat2);
            delta         = (clat1 * slat2) - (slat1 * clat2 * cdlong);
            delta         = sq(delta);
            delta += sq(clat2 * sdlong);
            delta        = sqrt(delta);
            float denom = (slat1 * slat2) + (clat1 * clat2 * cdlong);
            delta        = atan2(delta, denom);
            return delta * 6372795;
        }

        float GPSCoordinate::CourseTo(float lat1, float long1, float lat2,
                                       float long2)
        {
            float dlon = radians(long2 - long1);
            lat1        = radians(lat1);
            lat2        = radians(lat2);
            float a1   = sin(dlon) * cos(lat2);
            float a2   = sin(lat1) * cos(lat2) * cos(dlon);
            a2          = cos(lat1) * sin(lat2) - a2;
            a2          = atan2(a1, a2);
            if (a2 < 0.0)
            {
                a2 += TWO_PI;
            }
            return degrees(a2);
        }

        std::pair<float, float> GPSCoordinate::GetIntermediatePoint(GPSCoordinate src,
                                                                      GPSCoordinate dest,
                                                                      float distance)
        {
            float f = distance / GPSCoordinate::DistanceBetween(
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

    }  // namespace gps
}  // namespace sensor