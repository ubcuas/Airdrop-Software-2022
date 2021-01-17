#include <comm/oled.h>
#include <constants.h>

namespace display
{
    OLED::OLED()
    {
        connected = false;
        display   = Adafruit_SSD1306(config::SCREEN_WIDTH, config::SCREEN_HEIGHT, &Wire,
                                   config::OLED_RESET);
        if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
        {  // Address 0x3C for 128x32
            Serial.println(F("SSD1306 allocation failed"));
        }
        connected = true;

        displayDebugMessage(&data);
    }
    void OLED::displayDebugMessage(oled_dict *input)
    {
        display.clearDisplay();
        display.setTextSize(1);               // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE);  // Draw white text
        display.setCursor(0, 0);              // Start at top-left corner
        display.printf("cal:%d dist:%.4g\n", input->calibration, input->distance);
        display.printf("h:%04.1f alt:%04.2f\n", input->compass_heading, input->altitude);
        display.printf("gps:%d t_h: %.3f\n", input->gps_fix, input->target_heading);
        display.printf("State:%s\n", input->state.c_str());
        display.display();
    }
}  // namespace display