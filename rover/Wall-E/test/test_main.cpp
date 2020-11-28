#include <Arduino.h>
#include <pin_assignment.h>
#include <sensor/sensor.h>
#include <unity.h>

#include "test_driver/sensor/test_gps.h"
#include "test_driver/test_sensor_driver.h"
#include "test_driver/controller/test_manual_controller.h"

// void setUp(void) {
// // set stuff up here
// }

// void tearDown(void) {
// // clean stuff up here
// }

void test_led_builtin_pin_number(void)
{
    TEST_ASSERT_EQUAL(13, LED_BUILTIN);
}

void test_led_state_high(void)
{
    digitalWrite(LED_BUILTIN, HIGH);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(LED_BUILTIN));
}

void test_led_state_low(void)
{
    digitalWrite(LED_BUILTIN, LOW);
    TEST_ASSERT_EQUAL(LOW, digitalRead(LED_BUILTIN));
}

// Add your tests here

void test_sensor_driver()
{
    test::TestSensorDriver test = test::TestSensorDriver();
    TEST_ASSERT_EQUAL(255, pin::TEST_DUMMPY);
    test.TestGPS();
    test.TestCompass();
    test.TestMotor();
    test.TestRC();
}

void test_gps_driver()
{
    test::TestGPS gps = test::TestGPS();
}


void setup()
{
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();  // IMPORTANT LINE!

    RUN_TEST(test_gps_driver);

    RUN_TEST(test_sensor_driver);


    // example blink
    RUN_TEST(test_led_builtin_pin_number);

    pinMode(LED_BUILTIN, OUTPUT);
}

uint8_t i          = 0;
uint8_t max_blinks = 5;

void loop()
{
    if (i < max_blinks)
    {
        RUN_TEST(test_led_state_high);
        delay(500);
        RUN_TEST(test_led_state_low);
        delay(500);
        i++;
    }
    else if (i == max_blinks)
    {
        UNITY_END();  // stop unit testing
    }
}