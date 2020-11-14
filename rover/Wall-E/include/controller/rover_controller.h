#pragma once
#include <tuple>

namespace controller
{
    class RoverController{
        public:
            RoverController();
            static std::pair<double, double> MotorController(int throttle, int turn_angle);
            static std::pair<double, double> RCController(int throttle_value, int yaw_value);
    };
} // namespace controller
