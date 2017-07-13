
#include "../headers/display.h"
#include "Arduino.h"
#include <string.h>
#include <stdio.h>

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
		lcd.print(input);
		Serial.print(input);
	}
	
	void printErr(char const * output) {
		lcd.setCursor(shift + 8 - strlen(output) / 2, 1);
		lcd.print(output);
		Serial.println("");
		Serial.println(output);
	}

	void printAns(int output) {
		char buf[32];
		sprintf(buf, "%d", output);
		lcd.setCursor(shift + 8 - strlen(buf) / 2, 1);
		lcd.print(buf);
		Serial.println(output);
	}

	void clear() {
		lcd.clear();
		lcd.setCursor(7, 0);
		pos = 0, shift = 0;
	}
	
}
