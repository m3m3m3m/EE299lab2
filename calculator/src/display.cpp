
#include "../headers/display.h"
#include "Arduino.h"

namespace display {
	LiquidCrystal lcd(LCD_PORT);
	int pos, shift;
	void begin() {
		lcd.begin(16, 2);
		pos = 0, shift = 0;
		lcd.setCursor(7, 0);
	}

	void addCmd(char input) {
		pos++;
		if(pos != 1 && pos % 2 == 1) {
			lcd.scrollDisplayLeft();
			shift += 1;
		}
		//lcd.setCursor(pos/2+7,0);
		lcd.print(input);
	}

	void addCmd(int input) {
		pos++;
		if(pos != 1 && pos % 2 == 1) lcd.scrollDisplayLeft();
		//lcd.setCursor(pos/2+7,0);
		lcd.print(input);
	}
	
	void printAns(char const * output) {
		lcd.setCursor(4, 1);
		lcd.print(output);
	}

	void printAns(int output) {
		lcd.setCursor(4, 1);
		lcd.print(output);
	}

	void clear() {
		lcd.clear();
		lcd.setCursor(7, 0);
		pos = 0, shift = 0;
	}
	
}
