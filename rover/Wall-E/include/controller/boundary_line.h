#pragma once
#include <constants.h>
#include <sensor/gps_coordinate.h>

namespace controller
{
    class BoundaryLine
    {
       private:
        sensor::gps::GPSCoordinate* p1;
        sensor::gps::GPSCoordinate* p2;

       public:
        BoundaryLine(sensor::gps::GPSCoordinate p1, sensor::gps::GPSCoordinate p2);
        std::pair<float, float> GetP1() const;
        std::pair<float, float> GetP2() const;
        float GetSlope();
        bool IsVertical();
        bool IsHorizontal();
    };
}  // namespace controller