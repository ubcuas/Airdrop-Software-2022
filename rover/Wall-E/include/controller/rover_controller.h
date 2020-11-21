#pragma once
#include <tuple>

namespace controller
{
    class RoverController
    {
       private:
       public:
        RoverController();

        /**
         * @brief
         *
         * @param throttle 0-100 percent
         * @param turn_angle -180 to 180 degree, clockwise positive
         * @return std::pair<double, double> left motor speed, right motor speed
         */
        static std::pair<double, double> MotorController(int throttle, int turn_angle);

        /**
         * @brief
         *
         * @param throttle_value 1000-2000
         * @param yaw_value 1000-2000
         * @return std::pair<double, double> speed, turn angle
         */
        static std::pair<double, double> RCController(int throttle_value, int yaw_value);

        /**
         * @brief Landing detection algorithm. Takes input from
         *
         * @todo complete function signature.
         *
         */
        void LandingDetectionUpdate();

        bool GetLandingStatus();
    };
}  // namespace controller
