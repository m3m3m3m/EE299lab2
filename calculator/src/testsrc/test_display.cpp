
#include "Arduino.h"
#include "../../headers/display.h"
#include "../../headers/test.h"

using namespace display;

namespace test { 
	namespace display {
		void setup() {
			begin();
		}

		void loop() {
			for (int i = 0; i < 7; i++)
				addCmd('i');
			printErr("1234567890");
			delay(10000);
			clear();
		}
	}
}
