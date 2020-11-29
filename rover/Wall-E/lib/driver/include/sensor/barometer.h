#pragma once

#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <Wire.h>
#include <sensor/sensor.h>
#include <utility/imumaths.h>

namespace sensor
{
    class BMP280Barometer : public Sensor
    {
       private:
        Adafruit_BMP280 bmp;

       public:
        using Sensor::Sensor;
        virtual bool CheckConnection() override;

        virtual void Attach() override;

        virtual void Update() override;

        virtual bool Calibrate() override;

        virtual void Debug() override;
        
        double starting_altitude;
        double current_altitude;

        double takeoff_altitude;
        bool start_landing_detection;


        double GetAltitude() const;
    };
}  // namespace sensor
