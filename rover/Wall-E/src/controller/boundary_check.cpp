#include "controller/boundary_check.h"

namespace controller
{
    bool Boundary::IsWithinBoundary(float latitude, float longitude)
    {
        BoundaryLine top_line(boundary::p1, boundary::p2);
        BoundaryLine left_line(boundary::p2, boundary::p3);
        BoundaryLine bottom_line(boundary::p3, boundary::p4);
        BoundaryLine right_line(boundary::p4, boundary::p1);

        float upper_latitude_1 = (top_line.IsHorizontal()) ? (top_line.GetP1().first) : ((longitude - top_line.GetP1().second) * top_line.GetSlope() + top_line.GetP1().first);
        float upper_latitude_2 = (left_line.IsHorizontal()) ? (left_line.GetP1().first) : ((longitude - left_line.GetP1().second) * left_line.GetSlope() + left_line.GetP1().first);

        float upper_bound = std::min(upper_latitude_1, upper_latitude_2);

        float lower_latitude_1 = (bottom_line.IsHorizontal()) ? (bottom_line.GetP1().first) : ((longitude - bottom_line.GetP1().second) * bottom_line.GetSlope() + bottom_line.GetP1().first);
        float lower_latitude_2 = (right_line.IsHorizontal()) ? (left_line.GetP1().first) : ((longitude - left_line.GetP1().second) * left_line.GetSlope() + left_line.GetP1().first);

        float lower_bound = std::max(lower_latitude_1, lower_latitude_2);

        return (latitude <= upper_bound && latitude >= lower_bound);
    }

    bool Boundary::IsWithinBoundary(sensor::gps::GPSCoordinate coordinate)
    {
        return IsWithinBoundary(coordinate.GetLatitude(), coordinate.GetLongitude());
    }

    bool Boundary::IsWithinBoundary(std::pair<float, float> coordinate)
    {
        return IsWithinBoundary(coordinate.first, coordinate.second);
    }

}  // namespace controller