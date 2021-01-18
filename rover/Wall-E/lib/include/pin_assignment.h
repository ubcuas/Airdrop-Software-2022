/**
 * @file pin_assignment.h
 * @brief
 * @version 1.0
 * @date 2021-01-17
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once
#include <Arduino.h>
namespace pin
{
    // Teensy pin assignment
    // TODO: at calibration, check pin assignments and make sure there is no duplicate
    const static uint8_t TEST_DUMMPY   = 255;
    const static uint8_t MOTOR_L_PWM   = 2;
    const static uint8_t MOTOR_L_DIR_A = 3;  // direction controll pin
    const static uint8_t MOTOR_L_DIR_B = 4;  // direction controll pin
    const static uint8_t MOTOR_R_PWM   = 7;
    const static uint8_t MOTOR_R_DIR_A = 8;  // direction controll pin
    const static uint8_t MOTOR_R_DIR_B = 9;  // direction controll pin

    const static uint8_t RC_INPUT = 6;

    // I2C
    const static uint8_t SCL        = 19;
    const static uint8_t SDA        = 18;
    const static uint8_t BMP280_SCL = SCL;
    const static uint8_t BMP280_SDA = SDA;
    const static uint8_t BNO055_SCL = SCL;
    const static uint8_t BNO055_SDA = SDA;
    const static uint8_t OLED_SCL   = SCL;
    const static uint8_t OLED_SDA   = SDA;

    // Serial
    const static uint8_t GPS_TX  = 1;
    const static uint8_t GPS_RX  = 0;
    const static uint8_t LCD_TX  = 20;
    const static uint8_t LCD_RX  = 21;
    const static uint8_t XBEE_TX = 14;
    const static uint8_t XBEE_RX = 15;

    const static uint8_t SERVO_PIN = 5;

    const static uint8_t BMP_SCK  = 13;
    const static uint8_t BMP_MISO = 12;
    const static uint8_t BMP_MOSI = 11;
    const static uint8_t BMP_CS   = 10;

    const static uint8_t THROTTLE_PIN = 11;
    const static uint8_t YAW_PIN      = 12;
    const static uint8_t SWITCH_PIN   = 2;  // replace, this is not a pwm pin

}  // namespace pin
