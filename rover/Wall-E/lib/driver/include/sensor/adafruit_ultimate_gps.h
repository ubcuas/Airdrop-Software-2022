#pragma once

#include <sensor/gps_coordinate.h>
#include <sensor/sensor.h>
#include <tuple>

namespace sensor
{
    namespace gps
    {
        class AdafruitUltimateGPS : public Sensor
        {
           private:
            GPSCoordinate* current_location;
            GPSCoordinate* last_location;

           public:
            using Sensor::Sensor;

            void WaitForGPSConnection();

            std::pair<double, double> GetCurrentGPSCoordinate() const;

            std::pair<double, double> GetLastGPSCoordinate() const;

            virtual bool CheckConnection() override;

            virtual void Attach() override;

            virtual void Update() override;

            virtual bool Calibrate() override;

            virtual bool Stop() override;

            virtual void Debug() override;

            virtual void Read();
        };
    }  // namespace gps

}  // namespace sensor
