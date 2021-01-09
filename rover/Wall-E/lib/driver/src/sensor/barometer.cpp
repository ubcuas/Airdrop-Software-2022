
#include <constants.h>
#include <pin_assignment.h>
#include <sensor/barometer.h>
namespace sensor
{
    namespace barometer
    {
        bool BMP280Barometer::CheckConnection()
        {
            return true;
        }

        void BMP280Barometer::Attach()
        {
            switch (mode)
            {
                case LogicMode::I2C:
                {
                    bmp = new Adafruit_BMP280(&Wire1);
                    break;
                };
                case LogicMode::SPI:
                {
                    bmp = new Adafruit_BMP280(pin::BMP_CS, pin::BMP_MOSI, pin::BMP_MISO,
                                              pin::BMP_SCK);
                };
                default:
                    break;
            }

            bmp->setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                             Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                             Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                             Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                             Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

            if (!bmp->begin())
            {
                /* There was a problem detecting the BNO055 ... check your connections
                 */
                Serial.print("No BMP280 detected");
                while (1)
                {
                    // Serial.println("?");
                }
            }

            starting_altitude       = GetAltitude() + estimation::DELTA_HEIGHT_THRESHOLD;
            takeoff_altitude        = GetAltitude();
            start_landing_detection = false;
        }  // namespace sensor

        void BMP280Barometer::Update()
        {
            current_altitude = bmp->readAltitude(1013.25);
        }

        bool BMP280Barometer::Calibrate()
        {
            return false;
        }

        void BMP280Barometer::Debug()
        {
            Serial.print("Temperature = ");
            Serial.print(bmp->readTemperature());
            Serial.println(" *C");

            Serial.print("Pressure = ");
            Serial.print(bmp->readPressure());
            Serial.println(" Pa");

            Serial.print("Approx altitude = ");
            Serial.print(bmp->readAltitude(1013.25)); /* Adjusted to local forecast! */
            Serial.println(" m");
        }
        double BMP280Barometer::GetAltitude() const
        {
            return current_altitude;
        }
    }  // namespace barometer
}  // namespace sensor
