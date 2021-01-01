#include <sensor/gps_coordinate.h>
namespace sensor
{
    namespace gps
    {
        GPSCoordinate::GPSCoordinate(double lat, double longi)
        {
            this->latitude  = lat;
            this->longitude = longi;
        }

        void GPSCoordinate::SetLatitude(double lat)
        {
            this->latitude = lat;
        }
        void GPSCoordinate::SetLongitude(double longi)
        {
            this->longitude = longi;
        }

        double GPSCoordinate::GetLatitude() const
        {
            return this->latitude;
        }

        double GPSCoordinate::GetLongitude() const
        {
            return this->longitude;
        }

        double GPSCoordinate::GetDistance(GPSCoordinate dest)
        {
            double distance = GPSCoordinate::DistanceBetween(
                latitude, longitude, dest.latitude, dest.longitude);
            return distance;
        }

        double GPSCoordinate::GetHeading(GPSCoordinate dest)
        {
            double heading = GPSCoordinate::CourseTo(latitude, longitude, dest.latitude,
                                                     dest.longitude);
            return heading;
        }

        double GPSCoordinate::GetDistanceBetween(GPSCoordinate src, GPSCoordinate dest)
        {
            double distance =
                GPSCoordinate::DistanceBetween(src.GetLatitude(), src.GetLongitude(),
                                               dest.GetLatitude(), dest.GetLongitude());
            return distance;
        }

        double GPSCoordinate::GetHeadingBetween(GPSCoordinate src, GPSCoordinate dest)
        {
            double heading =
                GPSCoordinate::CourseTo(src.GetLatitude(), src.GetLongitude(),
                                        dest.GetLatitude(), dest.GetLongitude());
            return heading;
        }

        double GPSCoordinate::DistanceBetween(double lat1, double long1, double lat2,
                                              double long2)
        {
            double delta  = radians(long1 - long2);
            double sdlong = sin(delta);
            double cdlong = cos(delta);
            lat1          = radians(lat1);
            lat2          = radians(lat2);
            double slat1  = sin(lat1);
            double clat1  = cos(lat1);
            double slat2  = sin(lat2);
            double clat2  = cos(lat2);
            delta         = (clat1 * slat2) - (slat1 * clat2 * cdlong);
            delta         = sq(delta);
            delta += sq(clat2 * sdlong);
            delta        = sqrt(delta);
            double denom = (slat1 * slat2) + (clat1 * clat2 * cdlong);
            delta        = atan2(delta, denom);
            return delta * 6372795;
        }

        double GPSCoordinate::CourseTo(double lat1, double long1, double lat2,
                                       double long2)
        {
            double dlon = radians(long2 - long1);
            lat1        = radians(lat1);
            lat2        = radians(lat2);
            double a1   = sin(dlon) * cos(lat2);
            double a2   = sin(lat1) * cos(lat2) * cos(dlon);
            a2          = cos(lat1) * sin(lat2) - a2;
            a2          = atan2(a1, a2);
            if (a2 < 0.0)
            {
                a2 += TWO_PI;
            }
            return degrees(a2);
        }

        std::pair<double, double> GPSCoordinate::GetIntermediatePoint(GPSCoordinate src,
                                                                      GPSCoordinate dest,
                                                                      double distance)
        {
            double f = distance / GPSCoordinate::DistanceBetween(
                                      src.GetLatitude(), src.GetLongitude(),
                                      dest.GetLatitude(), dest.GetLongitude());
            double delta = distance / 6372795;  // m
            double a     = sin((1 - f) * delta) / sin(delta);
            double b     = sin(f * delta) / sin(delta);
            double x     = a * cos(src.GetLatitude()) * cos(src.GetLongitude()) +
                       b * cos(dest.GetLatitude()) * cos(dest.GetLongitude());
            double y = a * cos(src.GetLatitude()) * sin(src.GetLongitude()) +
                       b * cos(dest.GetLatitude()) * sin(dest.GetLongitude());
            double z        = a * cos(src.GetLatitude()) + b * cos(dest.GetLatitude());
            double theta_i  = atan2(z, sqrt(pow(x, 2) + pow(y, 2)));
            double lambda_i = atan2(y, x);
            return std::make_pair(theta_i, lambda_i);
        }
        std::pair<double, double> GPSCoordinate::ConvertToPair() const
        {
            return std::make_pair(GPSCoordinate::GetLatitude(),
                                  GPSCoordinate::GetLongitude());
        }

    }  // namespace gps
}  // namespace sensor