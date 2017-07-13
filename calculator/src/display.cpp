
#include "../headers/display.h"
#include "Arduino.h"

namespace display {
	LiquidCrystal lcd(LCD_PORT);
	void init() {
		lcd.begin(16, 2);
	}

	
}
