#pragma once

#include "controller/rover_controller.h"

namespace test
{
    class TestManualController
    {
       private:
       public:
        TestManualController();

        /**
         * @brief Test when input is 0 and 0, motor should return 0
         *
         */
        void TestStop();

        /**
         * @brief Test straight forward output
         *
         */
        void TestForward();

        /**
         * @brief Test left turn
         *
         */
        void TestLeft();

        /**
         * @brief Test right turn
         *
         */
        void TestRight();

        /**
         * @brief Test return for value given that's out of bounds
         *
         */
        void TestOutOfBounds();

        /**
         * @brief Test RC Controller output
         *
         */
        void TestRCController_1();

        /**
         * @brief Test RC Controller output
         *
         */
        void TestRCController_2();

        /**
         * @brief Test backwards, rover should not be able to go backwards
         *
         */
        void TestBackwards();
    };
}  // namespace test