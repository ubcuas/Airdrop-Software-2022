#include "test_gps.h"

namespace test
{
    TestGPS::TestGPS()
    {
        gps = std::make_shared<sensor::gps::AdafruitUltimateGPS>();
    }
}  // namespace test
