#include "Arduino.h"
#include "headers/constant.h"
#include "headers/phase.h"
#include "headers/test.h"

#if PHASE == 0

void setup() {
    test::setup();
}

void loop() {
    test::loop();
}

#else

void setup() {
    phase::setup();
}

void loop() {
    phase::loop();
}

#endif	// PHASE == 0
