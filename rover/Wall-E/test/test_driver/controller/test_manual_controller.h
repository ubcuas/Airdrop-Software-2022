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
    };
}  // namespace test