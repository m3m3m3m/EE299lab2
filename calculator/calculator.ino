//----------------------------------------------------------------
//  Module name:
//      calculator.ino
//  Languange:
//      Wiring/Arduino
//  Description:
//      The program takes user's input from the Serial Monitor and
//      prints the input and result on a LCD.
//  Author:
//      Mingxiao An, Man Sun, Muhan Li
//  Rev.0 12 July 2017
//  Rev.1 13 July 2017
//  Rev.2 16 July 2017
//----------------------------------------------------------------
#include "Arduino.h"
#include "headers/constant.h"
#include "headers/phase.h"
#include "headers/test.h"

#if PHASE == 0					// used for testing

// the setup routine runs once when you press reset:
void setup() {
	Serial.begin(BAUD_RATE);	// start serial port at baud rate
    test::setup();				// use the setup function in test namespace
}

// the loop routine runs over and over again forever:
void loop() {
    test::loop();				// use the loop function in test namespace
}

#else							// used for displaying

// the setup routine runs once when you press reset:
void setup() {
	Serial.begin(BAUD_RATE);	// start serial port at baud rate
    phase::setup();				// use the setup function in test namespace
}

// the loop routine runs over and over again forever:
void loop() {
    phase::loop();				// use the loop function in test namespace
}

#endif	// PHASE == 0
