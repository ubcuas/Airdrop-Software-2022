
#include <SoftwareSerial.h>
#include <constants.h>
#include <pin_assignment.h>
#include <sensor/adafruit_ultimate_gps.h>
#include <sensor/gps_coordinate.h>

// #ifndef ARDUINO
//         SoftwareSerial RoverSerial(pin::GPS_TX_PIN, pin::GPS_RX_PIN);  // arduino
// #else
#define RoverSerial                                                                      \
    Serial1  // teensy
             // #endif
namespace sensor
{
    namespace gps
    {
        bool AdafruitUltimateGPS::CheckConnection()
        {
            return GPS->fix;
        }

        bool AdafruitUltimateGPS::Calibrate()
        {
            Serial.print(this->sensor_name);
            Serial.println(" Calibrate");
            return false;
        }

        void AdafruitUltimateGPS::Debug()
        {
            Serial.printf("[GPS]\n====================\n");
            Serial.printf("Latitude: %f\n", current_location->GetLatitude());
            Serial.printf("Longitude: %f\n", current_location->GetLongitude());
            Serial.println("================");
        }

        void AdafruitUltimateGPS::Attach()
        {
            GPS = new Adafruit_GPS(&RoverSerial);

            current_location = new GPSCoordinate(estimation::DEFAULT_GPS_LATITUDE,
                                                 estimation::DEFAULT_GPS_LONGITUDE);
            last_location    = new GPSCoordinate(estimation::DEFAULT_GPS_LATITUDE,
                                              estimation::DEFAULT_GPS_LONGITUDE);
            GPS->begin(9600);
            GPS->sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
            GPS->sendCommand(PMTK_SET_NMEA_UPDATE_10HZ);
            GPS->sendCommand(PGCMD_ANTENNA);
            RoverSerial.println(PMTK_Q_RELEASE);
        }

        void AdafruitUltimateGPS::Update()
        {
            last_location->SetLatitude(current_location->GetLatitude());
            last_location->SetLongitude(current_location->GetLongitude());

            current_location->SetLatitude(GPS->latitude);
            current_location->SetLongitude(GPS->longitude);
        }

        void AdafruitUltimateGPS::Read()
        {
            char c = GPS->read();

            // (void)c;
            // if you want to debug, this is a good time to do it!

            // if (c)
            //     Serial.print(c);

            if (GPS->newNMEAreceived())
            {
                // Serial.println(GPS->lastNMEA());  // this also sets the
                // newNMEAreceived() flag to false
                if (!GPS->parse(GPS->lastNMEA()))
                    return;
            }
        }

        bool AdafruitUltimateGPS::Stop()
        {
            this->current_location->SetLatitude(estimation::DEFAULT_GPS_LATITUDE);
            this->current_location->SetLongitude(estimation::DEFAULT_GPS_LONGITUDE);

            return true;
        }

        bool AdafruitUltimateGPS::WaitForGPSConnection()
        {
            // TODO: complete this
            return true;
        }

        std::pair<double, double> AdafruitUltimateGPS::GetCurrentGPSCoordinate() const
        {
            return std::make_pair(current_location->GetLatitude(),
                                  current_location->GetLongitude());
        }
        std::pair<double, double> AdafruitUltimateGPS::GetLastGPSCoordinate() const
        {
            return std::make_pair(current_location->GetLatitude(),
                                  current_location->GetLongitude());
        }

    }  // namespace gps

}  // namespace sensor
