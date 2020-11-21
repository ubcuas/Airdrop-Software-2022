#pragma once
#include <Arduino.h>
namespace pin
{
    /**
     * @brief
     *
     */
    #ifndef Arduino
        const static uint8_t TEST_DUMMPY   = 255;
        const static uint8_t MOTOR_L_PWM   = 2;
        const static uint8_t MOTOR_L_DIR_A = 3;  // direction controll pin
        const static uint8_t MOTOR_L_DIR_B = 4;  // direction controll pin
        const static uint8_t MOTOR_R_PWM   = 7;
        const static uint8_t MOTOR_R_DIR_A = 8;  // direction controll pin
        const static uint8_t MOTOR_R_DIR_B = 9;  // direction controll pin

        const static uint8_t RC_INPUT = 6;

        const static uint8_t GPS_TX = 1;
        const static uint8_t GPS_RX = 0;
        const static uint8_t BNO055_SCL = 19;
        const static uint8_t BNO055_SDA = 18;
        const static uint8_t LCD_TX = 20;
        const static uint8_t LCD_RX = 21;

        const static uint8_t SERVO_PIN = 5;

        const static uint8_t BMP_SCK  = 13;
        const static uint8_t BMP_MISO = 12;
        const static uint8_t BMP_MOSI = 11;
        const static uint8_t BMP_CS   = 10;


    #else
        const static uint8_t TEST_DUMMPY   = 255;
        const static uint8_t MOTOR_L_PWM   = 1;
        const static uint8_t MOTOR_L_DIR_A = 3;  // direction controll pin
        const static uint8_t MOTOR_L_DIR_B = 4;  // direction controll pin
        const static uint8_t MOTOR_R_PWM   = 5;
        const static uint8_t MOTOR_R_DIR_A = 6;  // direction controll pin
        const static uint8_t MOTOR_R_DIR_B = 7;  // direction controll pin
        const static uint8_t RC_INPUT      = 2;
        const static uint8_t GPS_TX_PIN    = 9;
        const static uint8_t GPS_RX_PIN    = 8;
        const static uint8_t SERVO_PIN     = 10;
    #endif


}  // namespace pin
