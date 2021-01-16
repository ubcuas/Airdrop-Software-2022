/**
 * @file landing_controller.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-01-12
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once
#include <utility/imumaths.h>

#include <deque>
namespace controller
{
    class LandingController
    {
       private:
        bool landed;
        std::deque<imu::Vector<3>> linear_accel_history;
        imu::Vector<3> average;
        bool WithinLimit(double src, double val, double limit) const;
        uint32_t start_time;
        uint32_t end_time;

       public:
        LandingController();
        /**
         * @brief Landing detection algorithm. Takes input from
         *
         * @todo complete function signature.
         *
         */
        void LandingDetectionUpdate(imu::Vector<3> input);

        /**
         * @brief Return landing status
         *
         * @return true
         * @return false
         */
        bool GetLandingStatus() const;

        void Debug() const;
        
        /**
         * @brief Debug purpose only: test how long the timing is.
         * 
         */
        void Start();
        void End();
    };

}  // namespace controller