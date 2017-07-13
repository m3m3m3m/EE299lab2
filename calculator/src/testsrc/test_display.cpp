
#include "Arduino.h"
#include "../../headers/display.h"
#include "../../headers/test.h"

namespace test { 
	namespace display {

		void setup() {
			display::init();
		}

		void loop() {
			display::addCmd("x");
			delay(1000);
		}
	}
}
