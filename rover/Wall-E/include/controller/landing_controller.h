#pragma once
#include <Adafruit_BNO055.h>

#include <deque>
namespace controller
{
    class LandingController
    {
       private:
        bool landed;
        std::deque<bool> landing_status_state;
        imu::Vector<3> average;
        bool WithinLimit(double src, double val, double limit) const;

       public:
        LandingController();
        /**
         * @brief Landing detection algorithm. Takes input from
         *
         * @todo complete function signature.
         *
         */
        void LandingDetectionUpdate(double accelx, double accely, double accelz);
        bool GetLandingStatus() const;
    };

}  // namespace controller