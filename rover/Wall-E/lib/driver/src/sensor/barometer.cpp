
#include <constants.h>
#include <pin_assignment.h>
#include <sensor/barometer.h>
namespace sensor
{
    bool BMP280Barometer::CheckConnection()
    {
        return true;
    }

    void BMP280Barometer::Attach()
    {
        bmp = Adafruit_BMP280(pin::BMP_CS, pin::BMP_MOSI, pin::BMP_MISO, pin::BMP_SCK);

        bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                        Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                        Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                        Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                        Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

        while (!bmp.begin())
        {
            /* There was a problem detecting the BNO055 ... check your connections */
            while (1)
            {
            }
        }
        starting_altitude       = GetAltitude() + estimation::DELTA_HEIGHT_THRESHOLD;
        takeoff_altitude        = GetAltitude();
        start_landing_detection = false;
    }

    void BMP280Barometer::Update()
    {
        current_altitude = bmp.readAltitude(1013.25);
    }

    bool BMP280Barometer::Calibrate()
    {
        return false;
    }

    double BMP280Barometer::GetAltitude() const
    {
        return current_altitude;
    }

}  // namespace sensor
