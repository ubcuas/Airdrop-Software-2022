#include "controller/rover_controller.h"

#include <TinyGPS++.h>
#include <constants.h>
#include <math.h>
#include <pin_assignment.h>
#include <sensor/gps_coordinate.h>

namespace controller
{
    RoverController::RoverController(int dt)
        : dt(dt),
          q(imu::Vector<3>(0, 0, 0)),
          last_error(0),
          error_sum(0),
          KP(estimation::DEFAULT_KP),
          KI(estimation::DEFAULT_KI),
          KD(estimation::DEFAULT_KD)
    {
    }

    void RoverController::RoverControllerUpdate(imu::Vector<3> linear_accel,
                                                imu::Vector<3> orientation,
                                                imu::Vector<3> euler)
    {
        // euler is (Yaw, Roll, Pitch)
        q[0] += linear_accel.y() * 0.5 * pow((double)(dt) / 1000.0, 2);
        q[1] += linear_accel.x() * 0.5 * pow((double)(dt) / 1000.0, 2);
        q[2] = euler.x();
    }
    std::pair<double, double> RoverController::MotorController(
        std::pair<double, double> input)
    {
        double throttle   = input.first;
        double turn_angle = input.second;
        double left       = throttle;
        double right      = throttle;

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
    std::pair<double, double> RoverController::HeadingPIDController(
        std::pair<double, double> src, std::pair<double, double> dest,
        double current_heading, double current_dist)
    {
        // TODO: check the distance to determine the throttle
        double throttle = estimation::FAST_SPEED;
        if (current_dist < estimation::FINAL_SLOW_DOWN_THRESH)
        {
            throttle = estimation::SLOW_SPEED;
        }

        double turn_angle = sensor::gps::GPSCoordinate::CourseTo(src.first, src.second,
                                                                 dest.first, dest.second);

        double error = PIDErrorCorrection(current_heading, turn_angle);
        error_sum += error;
        error_sum = constrain(error_sum, estimation::I_MIN, estimation::I_MAX);

        double output = KP * error + KI * error_sum + KD * (error - last_error);

        output     = constrain(output, estimation::I_MIN, estimation::I_MAX);
        last_error = error;
        return std::make_pair(throttle, output);
    }

    double RoverController::PIDErrorCorrection(double current_heading, double turn_angle)
    {
        if ((turn_angle < current_heading) && (current_heading - turn_angle > 180))
        {
            return (360 + turn_angle) - current_heading;
        }
        else if ((current_heading < turn_angle) && (turn_angle - current_heading > 180))
        {
            return turn_angle - (current_heading + 360);
        }
        else
        {
            return turn_angle - current_heading;
        }
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
