//----------------------------------------------------------------
//  Module name:
//      test_display.cpp
//  Languange:
//      C++
//  Description:
//      This file provides a testing function for the module. It tests
//      whether the content can be properly displayed on the lcd.
//  Author:
//      Mingxiao An, Man Sun, Muhan Li
//  Rev.0 12 July 2017
//  Rev.1 13 July 2017
//  Rev.2 16 July 2017
//----------------------------------------------------------------
#include "Arduino.h"
#include "../../headers/display.h"
#include "../../headers/test.h"

using namespace display;

namespace test { 
    namespace display {             // define namespace for display test
        // the setup routine runs once when you press reset:
        void setup() {
            begin();                // begin() from display.h to prepare
        }

        // the loop routine runs over and over again forever:
        void loop() {
            // print i for 7 times with a second of delay
            for (int i = 0; i < 7; i++) {
                addCmd('i');
                delay(1000);
            }
            printErr("1234567890"); // print some message as an error
            delay(10000);           // delay 10 seconds to check
            clear();                // clear all contents on lcd
        }
    }
}
