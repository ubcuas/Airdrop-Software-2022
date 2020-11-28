#include <unity.h>

#include "test_driver/controller/test_manual_controller.h"
#include "test_driver/sensor/test_gps.h"
#include "test_driver/test_sensor_driver.h"

test::TestManualController contrl = test::TestManualController();

// Add your tests here

void test_sensor_driver()
{
    test::TestSensorDriver test = test::TestSensorDriver();
    TEST_ASSERT_EQUAL(255, pin::TEST_DUMMPY);
    test.TestGPS();
    test.TestCompass();
    test.TestMotor();
    test.TestRC();
}

void test_gps_driver()
{
    test::TestGPS gps = test::TestGPS();
    (void)gps;
}

void test_controller_driver_forward()
{
    contrl.TestForward();
}

void test_controller_driver_left()
{
    contrl.TestLeft();
}

void test_controller_driver_right()
{
    contrl.TestRight();
}

void test_controller_driver_out_of_bound()
{
    contrl.TestOutOfBounds();
}

void test_controller_driver_stop()
{
    contrl.TestStop();
}

void test_controller_driver_backward()
{
    contrl.TestBackwards();
}