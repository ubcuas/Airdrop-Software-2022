#include "controller/boundary_line.h"

namespace controller
{
    BoundaryLine::BoundaryLine(sensor::gps::GPSCoordinate p1, sensor::gps::GPSCoordinate p2)
    {
        this->p1 = &p1;
        this->p2 = &p2;
    }

    std::pair<float, float> BoundaryLine::GetP1() const
    {
        return p1->ConvertToPair();
    }

    std::pair<float, float> BoundaryLine::GetP2() const
    {
        return p2->ConvertToPair();
    }

    float BoundaryLine::GetSlope()
    {
        if (IsVertical()) {
            return 0;
        } else {
            return (p2->GetLatitude() - p1->GetLatitude()) / (p2->GetLongitude() - p1->GetLongitude());
        }
    }

    bool BoundaryLine::IsVertical()
    {
        return (p1->GetLongitude() == p2->GetLongitude());
    }

    bool BoundaryLine::IsHorizontal()
    {
        return (p1->GetLatitude() == p2->GetLatitude());
    }

}  // namespace controller