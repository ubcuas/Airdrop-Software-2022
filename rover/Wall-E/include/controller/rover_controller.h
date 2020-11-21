#pragma once
#include <tuple>
#include "sensor/gps_coordinate.h"

namespace controller
{
    class RoverController{
        private:

        public:
            RoverController();
            static std::pair<double, double> MotorController(int throttle, int turn_angle);
            static std::pair<double, double> RCController(int throttle_value, int yaw_value);
            static std::pair<double, double> AutoController(sensor::gps::GPSCoordinate src, sensor::gps::GPSCoordinate dest);

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
             * @param src  the current gps coordinate
             * @param dest the target gps coordinate
             * @returns the angle 
             */
            static double HeadingController(sensor::gps::GPSCoordinate src, sensor::gps::GPSCoordinate dest);

            void ArrivalDetectionUpdate();

            bool GetArrivalStatus();

    };
} // namespace controller
