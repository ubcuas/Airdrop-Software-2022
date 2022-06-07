#include <Arduino.h>
#include "Communication.h"

/*
 * Purpose: Communication with odroid on aircraft
 * Input: Current winch mode
 * Output: 0 (do nothing) or 1 (do something)
 */
int readSerial(int mode) {
    String input = "";
    int output = 0;

    // Read input
    if (Serial.available() > 1) {
        input = Serial.readStringUntil('\n');
    }

    // Confirm connection with odroid
    if (input == "uas") {
        Serial.println("uas");
    }

    // Signal to reel down
    if (mode == 1  &&  input == "AIRDROPBEGIN") {
        output = 1;
    }

    // Signal for emergency cancel while reeling down
    if (mode == 2  &&  input == "AIRDROPCANCEL") {
        output = 1;
    }

    return output;
}