
#include "../headers/display.h"
#include "Arduino.h"

namespace display {
	LiquidCrystal lcd(LCD_PORT);
	int pos;
	void init() {
		lcd.begin(16, 2);
		pos = 0;
	}

	void addCmd(char input) {
		pos++;
		if(pos % 2 == 1) lcd.scrollLeftDisplay();
		lcd.setCursor(pos/2+7,0);
		lcd.print(input);
	}
	

	
}
