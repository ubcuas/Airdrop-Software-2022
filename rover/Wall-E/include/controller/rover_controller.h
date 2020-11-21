#pragma once
#include <tuple>

namespace controller
{
    class RoverController{
        private:

        public:
            RoverController();
            static std::pair<double, double> MotorController(int throttle, int turn_angle);
            static std::pair<double, double> RCController(int throttle_value, int yaw_value);

            /**
             * @brief Landing detection algorithm. Takes input from 
             * 
             * @todo complete function signature. 
             * 
             */
            void LandingDetectionUpdate();
            
            bool GetLandingStatus();

            /**
             * Calculates the necessary turn angle / heading difference between the target heading and current heading
             * @returns the angle 
             */
            float HeadingController();

            void ArrivalDetectionUpdate();

            bool GetArrivalStatus();

    };
} // namespace controller
