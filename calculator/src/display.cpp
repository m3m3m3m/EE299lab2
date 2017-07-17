//----------------------------------------------------------------
//  Module name:
//      display.cpp
//  Languange:
//      C++
//  Description:
//      The module implements the display functions and interfaces
//      of the calculator.
//  Author:
//      Mingxiao An, Man Sun, Muhan Li
//  Rev.0 12 July 2017
//  Rev.1 13 July 2017
//  Rev.2 16 July 2017
//----------------------------------------------------------------
#include "../headers/display.h"
#include "Arduino.h" 
#include <string.h>
#include <stdio.h>

namespace display {
	LiquidCrystal lcd(LCD_PORT);// initialize a lcd
	int count;// to store the number of the characters already input
	int shift;// to store how many times the lcd scrolls left
	
	void begin() {
		lcd.begin(16, 2);// 16 * 2 characters
		count = 0, shift = 0;// initialize to zero
		lcd.setCursor(7, 0);// set the cursor to the middle of the first line
	}

	//-----------------------------------------------------------  
	// addCmd 
	//  
	// Purpose:  
	//    add one character to the lcd as input  
	//  
	// Parameters:  
	//    [in] char - the character to be printed on the screen  
	//  
	// Returns:  
	//    void  
	// 
	// Author:  
	//    Mingxiao An, Man Sun, Muhan Li
	//  Rev.0 12 July 2017
	//  Rev.1 13 July 2017
	//  Rev.2 16 July 2017
	//-----------------------------------------------------------  
	void addCmd(char input) {
		count ++;							// increase the count by one 
		if(count != 1 && count % 2 == 1) {	// decide if the display should scroll left
			lcd.scrollDisplayLeft();		// scroll the display left
			shift ++;						// record the change
		}
		lcd.print(input);					// print the input char to the lcd
		Serial.print(input);				// print the input char to the serial monitor
	}
	
	void printErr(char const * output) {
		lcd.setCursor(shift + 8 - strlen(output) / 2, 1);
		lcd.print(output);
		Serial.println("");
		Serial.println(output);
	}

	void printAns(int output) {
		char buf[32];
		sprintf(buf, "%d", output);//returns the length of output
		lcd.setCursor(shift + 8 - strlen(buf) / 2, 1);
		//lcd.setCursor(shift + 8 - sprintf(buf,"%d",output) / 2, 1);
		lcd.print(buf);
		Serial.println(output);
	}

	void clear() {
		lcd.clear();
		lcd.setCursor(7, 0);
		count = 0, shift = 0;
	}
	
}
