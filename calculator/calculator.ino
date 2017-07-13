#include "Arduino.h"
#include "headers/constant.h"
#include "headers/phase.h"
#include "headers/test.h"

#if PHASE == 0

void setup() {
	Serial.begin(BAUD_RATE);
    test::setup();
}

void loop() {
    test::loop();
}

#else

void setup() {
	Serial.begin(BAUD_RATE);
    phase::setup();
}

void loop() {
    phase::loop();
}

#endif	// PHASE == 0
