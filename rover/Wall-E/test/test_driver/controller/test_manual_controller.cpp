#include "test_manual_controller.h"

#include <Arduino.h>
#include <constants.h>
#include <unity.h>

namespace test
{
    TestManualController::TestManualController() {}

    void TestManualController::TestStop()
    {
        auto result = controller::RoverController::MotorController(0, 0);
        TEST_ASSERT_EQUAL_MESSAGE(result.second, 0, "TestStop failed");
        TEST_ASSERT_EQUAL_MESSAGE(result.second, 0, "TestStop failed");
    }

    void TestManualController::TestForward()
    {
        auto result = controller::RoverController::MotorController(50, 0);
        TEST_ASSERT_EQUAL_MESSAGE(result.first, 50, "TestForward failed");
        TEST_ASSERT_EQUAL_MESSAGE(result.second, 50, "TestForward failed");
    }

    void TestManualController::TestLeft()
    {
        auto result = controller::RoverController::MotorController(50, -90);
        TEST_ASSERT_EQUAL_MESSAGE(result.first, -75, "TestLeft failed");
        TEST_ASSERT_EQUAL_MESSAGE(result.second, 75,"TestLeft failed");
    }

    void TestManualController::TestRight()
    {
        auto result = controller::RoverController::MotorController(50, 90);
        TEST_ASSERT_EQUAL_MESSAGE(result.first, 75, "TestRight Failed");
        TEST_ASSERT_EQUAL_MESSAGE(result.second, -75, "TestRight Failed");
    }

    void TestManualController::TestOutOfBounds()
    {
        auto result = controller::RoverController::MotorController(50, 360);
        TEST_ASSERT_FALSE_MESSAGE(result.first, 0);
        TEST_ASSERT_FALSE_MESSAGE(result.second, 0);
    }

    void TestManualController::TestBackwards() //should fail!
    {
        auto result = controller::RoverController::MotorController(-50, 0);
        TEST_ASSERT_FALSE_MESSAGE(result.first, 0);
        TEST_ASSERT_FALSE_MESSAGE(result.second, 0);
    }

}  // namespace test