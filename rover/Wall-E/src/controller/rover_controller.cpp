#include "controller/rover_controller.h"

#include <constants.h>
#include <math.h>
#include <pin_assignment.h>
#include <sensor/gps_coordinate.h>

namespace controller
{
    RoverController::RoverController(int dt) : dt(dt), q(imu::Vector<3>(0, 0, 0)) {}

    void RoverController::RoverControllerUpdate(imu::Vector<3> linear_accel,
                                                imu::Vector<3> orientation,
                                                imu::Vector<3> euler)
    {
        // euler is (Yaw, Roll, Pitch)
        q[0] += linear_accel.y() * 0.5 * pow((double)(dt)/1000.0, 2) ;
        q[1] += linear_accel.x() * 0.5 * pow((double)(dt)/1000.0, 2) ;
        q[2] = euler.x();
    }
    std::pair<double, double> RoverController::MotorController(int throttle,
                                                               int turn_angle)
    {
        double left  = throttle;
        double right = throttle;

        if (abs(turn_angle) > estimation::MOTOR_TURN_MIN_THRESH)
        {
            left = throttle + ((turn_angle > 0) ? 1 : -1) *
                                  ((turn_angle > 0) ? estimation::FULL_POWER - throttle
                                                    : estimation::FULL_POWER + throttle) *
                                  abs(turn_angle) / estimation::FULL_ANGLE;
            right =
                throttle + ((turn_angle < 0) ? 1 : -1) *
                               ((turn_angle < 0) ? estimation::FULL_POWER - throttle
                                                 : estimation::FULL_POWER + throttle) *
                               abs(turn_angle) / estimation::FULL_ANGLE;
        }

        return std::make_pair(left, right);
    }

    std::pair<double, double> RoverController::RCController(int throttle_value,
                                                            int yaw_value)
    {
        // mapping input transmitter val to output motor val

        int mappedSpeed = (throttle_value - magic::LOW_READING) / magic::PERCENTAGE;

        int mappedAngle =
            ((yaw_value - magic::LOW_READING) / magic::NUM_DEGREES) - magic::DEGREE_RANGE;

        return std::make_pair(mappedSpeed, mappedAngle);
    }
    std::pair<double, double> RoverController::AutoController(
        std::pair<double, double> src, std::pair<double, double> dest)
    {
        double throttle = 100;
        double turn_angle{HeadingController(src, dest)};

        return std::make_pair(throttle, turn_angle);
    }

    double RoverController::HeadingController(std::pair<double, double> src,
                                              std::pair<double, double> dest)
    {
        double turn_angle = sensor::gps::GPSCoordinate::CourseTo(src.first, src.second,
                                                                 dest.first, dest.second);

        return (turn_angle - 180);
    }

    void RoverController::Debug()
    {
        Serial.printf("[State model]\n========== \n");
        Serial.printf("(x: %.3f m, y: %.3f m, theta: %f degree)\n", q[0], q[1], q[2]);
        Serial.printf("");
        Serial.printf("");
        Serial.printf("");
    }
}  // namespace controller
