#pragma once
#include <constants.h>
#include <sensor/gps_coordinate.h>
#include <controller/boundary_line.h>
#include <algorithm>
#include <list>

namespace controller
{
    class Boundary
    {
       private:
        
       public:
        static bool IsWithinBoundary(float latitude, float longitude);
        static bool IsWithinBoundary(const sensor::gps::GPSCoordinate coordinate);
        static bool IsWithinBoundary(const std::pair<float, float> coordinate);
    };
}  // namespace controller