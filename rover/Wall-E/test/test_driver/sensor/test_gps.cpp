#include "test_gps.h"

namespace test
{
    TestGPS::TestGPS()
    {
        sensor::gps::AdafruitUltimateGPS gps = sensor::gps::AdafruitUltimateGPS("it's a test");
    }
}  // namespace test
