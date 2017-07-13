
#include "Arduino.h"
#include "../../headers/test.h"

namespace test { 
	namespace display {
		
		int led = 10;

		void setup() {
			pinMode(led, OUTPUT);
		}

		void loop() {
			digitalWrite(led, HIGH);
			delay(1000);
			digitalWrite(led, LOW);
			delay(1000);
		}
	}
}
