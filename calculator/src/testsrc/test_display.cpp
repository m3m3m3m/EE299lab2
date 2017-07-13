
#include "Arduino.h"
#include "../../headers/display.h"
#include "../../headers/test.h"

using display::begin;
using display::addCmd;

namespace test { 
	namespace display {

		void setup() {
			begin();
		}

		void loop() {
			addCmd('x');
			delay(1000);
		}
	}
}
