
#include "../headers/display.h"
#include "Arduino.h"

namespace display {
	LiquidCrystal lcd(LCD_PORT);
	int pos;
	void begin() {
		lcd.begin(16, 2);
		pos = 0;
		lcd.setCursor(7, 0);
	}

	void addCmd(char input) {
		pos++;
		if(pos != 1 && pos % 2 == 1) lcd.scrollDisplayLeft();
		//lcd.setCursor(pos/2+7,0);
		lcd.print(input);
	}
	

	
}
