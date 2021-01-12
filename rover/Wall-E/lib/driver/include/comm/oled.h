#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

namespace display
{
    struct oled_dict
    {
        float altitude  = 0;
        float latitude  = 0;
        float longitude = 0;
        float heading   = 0;
        float x         = 0;
        float y         = 0;
        float x_dot     = 0;
        float y_dot     = 0;
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