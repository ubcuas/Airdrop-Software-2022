#include "controller/landing_controller.h"

#include <constants.h>

namespace controller
{
    LandingController::LandingController()
    {
        landed = false;
        landing_status_state.resize(estimation::LANDING_DETECTION_HISTORY_LENGTH);
    }
    bool LandingController::GetLandingStatus() const
    {
        return landed;
    }
    bool LandingController::WithinLimit(double src, double val, double limit) const
    {
        return false;
    }
    void LandingController::LandingDetectionUpdate(double accelx, double accely,
                                                   double accelz)
    {
        if (landed)
        {
            return;
        }
        // add to the average
        if (WithinLimit(average.x(), accelx, estimation::LANDING_ACCEL_THRESH) &&
            WithinLimit(average.y(), accely, estimation::LANDING_ACCEL_THRESH) &&
            WithinLimit(average.z(), accelz, estimation::LANDING_ACCEL_THRESH))
        {
            landing_status_state.push_back(true);
        }
        else
        {
            landing_status_state.push_back(false);
        }
        landing_status_state.pop_front();

        // check if confirm landing
        int count = 0;
        for (bool val : landing_status_state)
        {
            if (val)
            {
                count += 1;
            }
        }

        if ((count / estimation::LANDING_DETECTION_HISTORY_LENGTH) >
            estimation::LANDING_STATUS_CONFIRM_THRESH)
        {
            landed = true;
        }
        else
        {
            // update average
            average[0] =
                (average[0] * (estimation::LANDING_DETECTION_HISTORY_LENGTH - 1) +
                 accelx) /
                estimation::LANDING_DETECTION_HISTORY_LENGTH;
            average[1] =
                (average[1] * (estimation::LANDING_DETECTION_HISTORY_LENGTH - 1) +
                 accely) /
                estimation::LANDING_DETECTION_HISTORY_LENGTH;
            average[2] =
                (average[2] * (estimation::LANDING_DETECTION_HISTORY_LENGTH - 1) +
                 accelz) /
                estimation::LANDING_DETECTION_HISTORY_LENGTH;
        }
    }
}  // namespace controller