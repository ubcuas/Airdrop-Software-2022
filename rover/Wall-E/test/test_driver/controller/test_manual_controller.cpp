#include "test_manual_controller.h"

#include <Arduino.h>
#include <unity.h>
namespace test
{
    TestManualController::TestManualController() {}

    void TestManualController::TestStop()
    {
        auto result = controller::RoverController::MotorController(0, 0);
        TEST_ASSERT_EQUAL(result.first, 0);
        TEST_ASSERT_EQUAL(result.second, 0);
    }

}  // namespace test