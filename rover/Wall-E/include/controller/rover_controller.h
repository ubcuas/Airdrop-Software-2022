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
#include <utility/imumaths.h>

#include <tuple>

namespace controller
{
    class RoverController
    {
       private:
        /* our state model(IMU's state model)
             +----------+
             |         *| RST   PITCH  ROLL  HEADING
         ADR |*        *| SCL
         INT |*        *| SDA     ^            /->
         PS1 |*        *| GND     |            |
         PS0 |*        *| 3VO     Y    X(Z)-->    \-Z(X)
             |         *| VIN
             +----------+
        */
        imu::Vector<2> position;
        imu::Vector<2> velocity;
        imu::Vector<2> acceleration;
        imu::Vector<2> w_theta_dot;  // [left wheel velocity, right wheel velocity]

        imu::Vector<3> q_dot;  //[x, y, theta], the state model of Rover
        int dt;                // (ms)
        double last_error;
        double error_sum;

        double KP;
        double KI;
        double KD;

        /**
         * @brief Correct the error angle. Since heading is between 0-360, there are some
         * edge cases where the angle roll over 360
         *
         * @param current_heading raw heading from sensor
         * @param turn_angle desired/input heading
         * @return double corrected error heading
         */
        double PIDErrorCorrection(double current_heading, double turn_angle);


       public:
        imu::Vector<3> q;  //[x, y, theta], the state model of Rover
        RoverController(int dt);

        /**
         * @brief Update the Rover state model q
         */
        void RoverControllerUpdate(imu::Vector<3> linear_accel,
                                   imu::Vector<3> orientation, imu::Vector<3> euler);
        /**
         * @brief Processes the passed speed and angle and returns the values passed to
         * the dc motors
         * @param input data pair of throttle value and turn angle (-180 to 180) degree
         * @returns a pair of values passed to the dc motors that will achieve the effect
         * described by the passed arguments
         */
        static std::pair<double, double> MotorController(std::pair<double, double> input);

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
         * Calculates the necessary turn angle / heading difference between the target
         * heading and current heading
         * @param src  the current gps coordinate
         * @param dest the target gps coordinate
         * @param heading the current heading (0-360) degree
         * @returns data pair of throttle value and turn angle (-180 to 180) degree
         */
        std::pair<double, double> HeadingPIDController(std::pair<double, double> src,
                                                       std::pair<double, double> dest,
                                                       double current_heading);


        void Debug();
    };
}  // namespace controller
