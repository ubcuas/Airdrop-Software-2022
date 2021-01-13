/**
 * @file rover_controller.h
 * @author your name (you@domain.com)
 * @brief Controller for the Rover, include rover's control mapping, estimation and
 * localization
 * @version 0.1
 * @date 2021-01-12
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <constants.h>
#include <tuple>

namespace controller
{
    class RoverController
    {
       private:

       public:
        RoverController();

        
        /**
         * @brief Processes the passed speed and angle and returns the values passed to
         * the dc motors
         * @param throttle 0 <= x <= 100
         * @param turn_angle angle to turn (-180 <= x <= 180)
         *                   Right: 0 < x <= 180
         *                   Left: -180 <= x < 0
         * @returns a pair of values passed to the dc motors that will achieve the effect
         * described by the passed arguments
         */
        static std::pair<double, double> MotorController(int throttle, int turn_angle);

        /**
         * @brief Manual mode: Converts the RC stick values to corresponding throttle and
         * turn angle
         * @param throttle_value throttle value of the RC
         * @param yaw_value yaw value of the RC
         * @returns a pair of values representing the throttle and turn angle indicated by
         * the RC
         */
        static std::pair<double, double> RCController(int throttle_value, int yaw_value);

        /**
         * @brief Auto mode: Determines the necessary speed and turn angle given a current
         * and target location
         * @param src latitude and longitude of the current location
         * @param dest latitude and longitude of the target location
         * @returns a pair of values representing the necessary speed and turn angle
         */
        static std::pair<double, double> AutoController(std::pair<double, double> src,
                                                        std::pair<double, double> dest);

        /**
         * Calculates the necessary turn angle / heading difference between the target
         * heading and current heading
         * @param src  the current gps coordinate
         * @param dest the target gps coordinate
         * @returns the angle
         */
        static double HeadingController(std::pair<double, double> src,
                                        std::pair<double, double> dest);


    };
}  // namespace controller
