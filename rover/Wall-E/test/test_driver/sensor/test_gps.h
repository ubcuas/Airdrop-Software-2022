#pragma once
#include <sensor/adafruit_ultimate_gps.h>

#include <memory>

namespace test
{
    class TestGPS
    {
       private:
        std::shared_ptr<sensor::gps::AdafruitUltimateGPS> gps;

       public:
        TestGPS();
    };
}  // namespace test
