/**
 * @file oled.h
 * @brief
 * @version 1.0
 * @date 2021-01-17
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

namespace display
{
    struct oled_dict
    {
        float altitude        = 0;
        float latitude        = 0;
        float longitude       = 0;
        float compass_heading = 0;
        uint8_t calibration   = 0;
        float distance        = 0;
        float target_heading  = 0;
        bool gps_fix          = 0;
        float x_dot           = 0;
        float y_dot           = 0;
        String state          = "";
    };
    class OLED
    {
       private:
        Adafruit_SSD1306 display;
        bool connected;
        oled_dict data;

       public:
        OLED();
        void displayDebugMessage(oled_dict *input);
    };
}  // namespace display