#include <Arduino.h>
#include "Communication.h"

/*
 * Purpose: Communication with odroid on aircraft
 * Input: Current winch mode
 * Output: 0 (do nothing) or 1 (reel down) or 2 (emergency)
 */
int readSerial(int mode) {
    String input = "";
    int output = 0;

    // Read input
    if (Serial.available() > 0) {
        input = Serial.readStringUntil('1');
    }

    // Confirm connection with odroid
    if (input == "uas") {
        Serial.println("uas");
    }

    // Signal to reel down
    if (mode == 1  &&  input == "AIRDROPBEGIN") {
        output = 1;
    }

    // Signal for emergency cancel while reeling down (NOT USING)
    if (mode == 2  &&  input == "AIRDROPCANCEL") {
        output = 2;
    }

    return output;
}