#pragma once
#include <sensor/adafruit_ultimate_gps.h>

namespace test
{
    /**
     * @brief integration test of all the driver code
     * 
     */
    class TestSensorDriver
    {
       private:
       public:
        TestSensorDriver();
        void TestGPS();
        void TestRC();
        void TestCompass();
        void TestMotor();
    };
}  // namespace test
