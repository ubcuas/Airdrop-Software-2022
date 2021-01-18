#include "controller/landing_controller.h"

#include <constants.h>

namespace controller
{
    LandingController::LandingController()
    {
        landed = false;
        linear_accel_history.resize(estimation::LANDING_DETECTION_HISTORY_LENGTH);
        start_time = 0;
        end_time   = 0;
    }
    bool LandingController::GetLandingStatus() const
    {
        return landed;
    }
    bool LandingController::WithinLimit(double src, double val, double limit) const
    {
        return (src < val + limit) && (src > val - limit);
    }
    void LandingController::LandingDetectionUpdate(imu::Vector<3> input)
    {
        if (landed)
        {
            // once landed, cannot be landed again.
            return;
        }

        // Update the queue
        linear_accel_history.push_back(input);
        linear_accel_history.pop_front();

        // Update avarage
        average = imu::Vector<3>(0, 0, 0);
        for (imu::Vector<3> data : linear_accel_history)
        {
            average.x() += data.x();
            average.y() += data.y();
            average.z() += data.z();
        }

        // check the timing
        if ((millis() - start_time) <
            timing::SLOW_TASK_MS * estimation::LANDING_DETECTION_HISTORY_LENGTH)
        {
            return;
        }


        average.x() /= estimation::LANDING_DETECTION_HISTORY_LENGTH;
        average.y() /= estimation::LANDING_DETECTION_HISTORY_LENGTH;
        average.z() /= estimation::LANDING_DETECTION_HISTORY_LENGTH;

        // check the average is within limit
        bool result = WithinLimit(average.x(), 0, estimation::LANDING_ACCEL_THRESH) &&
                      WithinLimit(average.y(), 0, estimation::LANDING_ACCEL_THRESH) &&
                      WithinLimit(average.z(), 0, estimation::LANDING_ACCEL_THRESH);

        // check if all value are within limit
        for (imu::Vector<3> data : linear_accel_history)
        {
            result &= WithinLimit(data.x(), average.x(),
                                  estimation::LANDING_ACCEL_HISTORY_THRESH) &&
                      WithinLimit(data.y(), average.y(),
                                  estimation::LANDING_ACCEL_HISTORY_THRESH) &&
                      WithinLimit(data.z(), average.z(),
                                  estimation::LANDING_ACCEL_HISTORY_THRESH);
        }

        landed = result;

        // TODO: add 
    }
    void LandingController::Debug() const
    {
        Serial.printf("[Landing]\n =============\n");
        Serial.printf("avg x: %f, y: %f, z: %f\n", average.x(), average.y(), average.z());
        Serial.printf("Elapsed time: %f\n", (millis() - start_time) / 1000.0);
        Serial.printf("Landing time: %f\n=========\n", (end_time - start_time) / 1000.0);
    }

    void LandingController::Start()
    {
        start_time = millis();
    }
    void LandingController::End()
    {
        end_time = millis();
    }
}  // namespace controller