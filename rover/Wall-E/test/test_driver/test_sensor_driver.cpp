#include "test_sensor_driver.h"

#include <Arduino.h>
#include <unity.h>

namespace test
{
    TestSensorDriver::TestSensorDriver() {}
    void TestSensorDriver::TestGPS()
    {
        TEST_ASSERT_EQUAL(1, 1);
    }

    void TestSensorDriver::TestRC()
    {
        TEST_ASSERT_EQUAL(1, 1);
    }

    void TestSensorDriver::TestCompass()
    {
        TEST_ASSERT_EQUAL(1, 1);
    }
    
    void TestSensorDriver::TestMotor()
    {
        TEST_ASSERT_EQUAL(1, 1);
    }
}  // namespace test
