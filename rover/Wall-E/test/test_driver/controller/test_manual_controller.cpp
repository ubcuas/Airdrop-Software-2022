#include "test_manual_controller.h"

#include <Arduino.h>
#include <unity.h>
#include <constants.h>

namespace test
{
    TestManualController::TestManualController() {}

    void TestManualController::TestStop()
    {
        auto result = controller::RoverController::MotorController(0, 0);
        TEST_ASSERT_EQUAL(result.first, 0);
        TEST_ASSERT_EQUAL(result.second, 0);
    }

    void TestManualController::TestForward()
    {
        auto result = controller::RoverController::MotorController(50, 0);
        TEST_ASSERT_EQUAL(result.first, 50);
        TEST_ASSERT_EQUAL(result.second, 50);
    }

    void TestManualController::TestLeft()
    {
        auto result = controller::RoverController::MotorController(50, -90);
        TEST_ASSERT_EQUAL(result.first, -75);
        TEST_ASSERT_EQUAL(result.second, 75);
    }

    void TestManualController::TestRight()
    {
        auto result = controller::RoverController::MotorController(50, 90);
        TEST_ASSERT_EQUAL(result.first, 75);
        TEST_ASSERT_EQUAL(result.second, -75);
    }

     void TestManualController::TestOutOfBounds()
    {
        auto result = controller::RoverController::MotorController(50, 360);
        TEST_ASSERT_EQUAL(result.first, 0);
        TEST_ASSERT_EQUAL(result.second, 0);
    }
}  // namespace test