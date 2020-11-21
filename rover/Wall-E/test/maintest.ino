#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
// #include <TinyGPS.h>

// you can change the pin numbers to match your wiring: (TX, RX)
SoftwareSerial mySerial(9, 8);
Adafruit_GPS GPS(&mySerial);

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences
#define GPSECHO  true

void setup()
{
  Serial.begin(115200);
  lcd.begin(16, 2);
  delay(5000);
  lcd.setCursor(0, 0);
  lcd.println("Initiating...");
  lcd.setCursor(0, 1);
  lcd.println("Looking for a fix");
  initGPS();
}

uint32_t gpsTimer = millis();
float targetLat = 49.156774299999995;
float targetLon = -123.13415359999999;

void loop()
{
  char c = GPS.read();
  // if you want to debug, this is a good time to do it!
  if ((c) && (GPSECHO))
    Serial.write(c);

  if (GPS.newNMEAreceived()) {
    //Serial.println(GPS.lastNMEA());   // this also sets the newNMEAreceived() flag to false

    if (!GPS.parse(GPS.lastNMEA()))
      return;
  }

  if (millis() - gpsTimer > 2000) {
    gpsTimer = millis();

    Serial.print("\nTime: ");
    if (GPS.hour < 10) { Serial.print('0'); }
    Serial.print(GPS.hour, DEC); Serial.print(':');
    if (GPS.minute < 10) { Serial.print('0'); }
    Serial.print(GPS.minute, DEC); Serial.print(':');
    if (GPS.seconds < 10) { Serial.print('0'); }
    Serial.print(GPS.seconds, DEC); Serial.print('.');
    if (GPS.milliseconds < 10) {
      Serial.print("00");
    } else if (GPS.milliseconds > 9 && GPS.milliseconds < 100) {
      Serial.print("0");
    }
    Serial.println(GPS.milliseconds);
    Serial.print("Date: ");
    Serial.print(GPS.day, DEC); Serial.print('/');
    Serial.print(GPS.month, DEC); Serial.print("/20");
    Serial.println(GPS.year, DEC);
    Serial.print("Fix: "); Serial.print((int)GPS.fix);
    Serial.print(" quality: "); Serial.println((int)GPS.fixquality);
    if (GPS.fix) {
      Serial.print("Location: ");
      Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
      Serial.print(", ");
      Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);

      float currentLat = convertToDecimalDegrees(GPS.latitude, GPS.lat);
      float currentLon = convertToDecimalDegrees(GPS.longitude, GPS.lon);
      
      float distance = 0;
      // TinyGPS::distance_between(currentLat, currentLon, targetLat, targetLon);
      float targetDirection = 0;
      // TinyGPS::course_to(currentLat, currentLon, targetLat, targetLon);

      lcd.setCursor(0, 0);
      lcd.print(currentLat, 3);
      lcd.setCursor(0, 8);
      lcd.print(currentLon, 3);
      lcd.setCursor(0, 1);
      lcd.print("Dist: ");
      lcd.print(distance, 5);

      Serial.print("Distance (m): "); Serial.println(distance);

      // Serial.print("Target Direction (degrees): "); Serial.println(targetDirection);
      // printDistanceAndBearing(distance, targetDirection);
      
      Serial.print("Speed (knots): "); Serial.println(GPS.speed);
      Serial.print("Angle: "); Serial.println(GPS.angle);
      Serial.print("Altitude: "); Serial.println(GPS.altitude);
      Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
    }
  }
  return;
}

void printCoords() {
  lcd.setCursor(0, 0);
  lcd.print("Lat: ");
  lcd.print(convertToDecimalDegrees(GPS.latitude, GPS.lat), 6);
  lcd.setCursor(0, 1);
  lcd.print("Lon: ");
  lcd.print(convertToDecimalDegrees(GPS.longitude, GPS.lon), 6);
}

void initGPS() {
  Serial.println("Adafruit GPS library basic test!");
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand(PGCMD_ANTENNA);

  delay(1000);
  mySerial.println(PMTK_Q_RELEASE);
}

float convertToDecimalDegrees(float degreesAndMinutes, char direction) {
  float degrees = floor(degreesAndMinutes / 100);
  float minutes = degreesAndMinutes - (degrees * 100);
  float decimalDegrees = degrees + minutes / 60;

  switch (direction)
  {
  case 'N': case 'E':
    return decimalDegrees;
  
  case 'S': case 'W':
    return decimalDegrees * (-1.0);

  default:
    return decimalDegrees;
  }
}

void printDistanceAndBearing(float distance, float bearing) {
  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print(distance, 5);
  lcd.setCursor(0, 1);
  lcd.print("Bearing: ");
  lcd.print(bearing, 2);
}