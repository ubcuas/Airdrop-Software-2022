#pragma once

#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <Wire.h>
#include <sensor/sensor.h>
#include <utility/imumaths.h>

namespace sensor
{
    namespace barometer
    {
        enum LogicMode
        {
            SPI,
            I2C
        };
        class BMP280Barometer : public Sensor
        {
           private:
            Adafruit_BMP280 bmp;
            LogicMode mode;
            double starting_altitude;
            double current_altitude;

            double takeoff_altitude;
            bool start_landing_detection;

           public:
            using Sensor::Sensor;

            BMP280Barometer(LogicMode mode, String name) : Sensor(name), mode(mode){};

            virtual bool CheckConnection() override;

            virtual void Attach() override;

            virtual void Update() override;

            virtual bool Calibrate() override;

            virtual void Debug() override;

            double GetAltitude() const;
        };
    }  // namespace barometer

}  // namespace sensor
