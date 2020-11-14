#include <controller/rover_controller.hpp>

namespace controller
{
    RoverController::RoverController() {}
    static std::pair<double, double> MotorController(int throttle, int turn_angle) {}
    static std::pair<double, double> RCController(int throttle_value, int yaw_value) {}
}  // namespace controller
