
#include <constants.h>
#include <pin_assignment.h>
#include <sensor/bmp280.h>
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
                    bmp = Adafruit_BMP280(&Wire);
                    break;
                };
                case LogicMode::SPI:
                {
                    bmp = Adafruit_BMP280(pin::BMP_CS, pin::BMP_MOSI, pin::BMP_MISO,
                                          pin::BMP_SCK);
                };
                default:
                    break;
            }

            bmp.reset();
            bmp.setSampling(Adafruit_BMP280::MODE_FORCED,      /* Operating Mode. */
                            Adafruit_BMP280::SAMPLING_X2,      /* Temp. oversampling */
                            Adafruit_BMP280::SAMPLING_X16,     /* Pressure oversampling */
                            Adafruit_BMP280::FILTER_X16,       /* Filtering. */
                            Adafruit_BMP280::STANDBY_MS_1000); /* Standby time. */

            // the default address for BMP280 is 0x77.
            if (!bmp.begin(0x76, 0x58))
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
            current_altitude = bmp.readAltitude(1013.25);
        }

        bool BMP280Barometer::Calibrate()
        {
            return false;
        }

        void BMP280Barometer::Debug()
        {
            Serial.printf("[Barometer]\n=========\n");
            Serial.print("Temperature = ");
            Serial.print(bmp.readTemperature());
            Serial.println(" *C");

            Serial.print("Pressure = ");
            Serial.print(bmp.readPressure());
            Serial.println(" Pa");

            Serial.print("Approx altitude = ");
            Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
            Serial.println(" m");

            Serial.printf("Sensor status %d \n", bmp.getStatus());

            Serial.println("=========");
        }
        double BMP280Barometer::GetAltitude() const
        {
            return current_altitude;
        }
    }  // namespace barometer
}  // namespace sensor
