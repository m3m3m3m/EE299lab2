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
	LiquidCrystal lcd(LCD_PORT);		// initialize a lcd
	int count;							// to store the number of the characters already input
	int shift;							// to store how many times the lcd scrolls left
	
	//-----------------------------------------------------------  
	// begin
	//  
	// Purpose:  
	//    initialize some local variables and prepare for the display
	// Parameters:  
	//    void  
	// Returns:  
	//    void  
	// Author:  
	//    Mingxiao An, Man Sun, Muhan Li
	//  Rev.0 12 July 2017
	//  Rev.1 13 July 2017
	//  Rev.2 16 July 2017
	//-----------------------------------------------------------  
	void begin() {
		lcd.begin(16, 2);				// 16 * 2 characters
		count = 0, shift = 0;			// initialize to zero
		lcd.setCursor(7, 0);			// set the cursor to the middle of the first line
	}

	//-----------------------------------------------------------  
	// addCmd 
	//  
	// Purpose:  
	//    add one character to the lcd as input   
	// Parameters:  
	//    [in] char - the character to be printed on the screen  
	// Returns:  
	//    void  
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
	
	//-----------------------------------------------------------  
	// printErr 
	//
	// Purpose:  
	//    print error information on the lcd  
	// Parameters:  
	//    [in] char* - the char array (contains error info) to be 
	//				   printed on the second line of lcd
	// Returns:  
	//    void  
	// Author:  
	//    Mingxiao An, Man Sun, Muhan Li
	//  Rev.0 12 July 2017
	//  Rev.1 13 July 2017
	//  Rev.2 16 July 2017
	//----------------------------------------------------------- 
	void printErr(char const * output) {
		lcd.setCursor(shift + 8 - strlen(output) / 2, 1);
											// set the cursor according to the length of the char array 
		lcd.print(output);					// print the error information on the lcd
		Serial.println("");					// print on a new line of serial monitor
		Serial.println(output);				// print the error information on the serial monitor
	}

	//-----------------------------------------------------------  
	// printAns 
	//  
	// Purpose:  
	//    print the result of calculation on lcd 
	// Parameters:  
	//    [in] int - the result to be printed on the lcd  
	// Returns:  
	//    void  
	// Author:  
	//    Mingxiao An, Man Sun, Muhan Li
	//  Rev.0 12 July 2017
	//  Rev.1 13 July 2017
	//  Rev.2 16 July 2017
	//----------------------------------------------------------- 
	void printAns(int output) {
		char buf[32];						// initialize a buffer to store result message
		sprintf(buf, "%d", output);			// push the integer as a string into the buffer
		lcd.setCursor(shift + 8 - strlen(buf) / 2, 1);
											// set the cursor according to the length of result
		lcd.print(buf);						// print the result stored in the buffer to lcd 
		Serial.println(output);				// print the integer result to the serial monitor
	}

	//-----------------------------------------------------------  
	// clear
	//  
	// Purpose:  
	//    clear all the content on lcd and set to the initial state 
	// Parameters:  
	//    void
	// Returns:  
	//    void  
	// Author:  
	//    Mingxiao An, Man Sun, Muhan Li
	//  Rev.0 12 July 2017
	//  Rev.1 13 July 2017
	//  Rev.2 16 July 2017
	//----------------------------------------------------------- 
	void clear() {
		lcd.clear();						// clear all the content on lcd and scroll back to initial					
		lcd.setCursor(7, 0);				// set the cursor to the beginnig point of input
		count = 0, shift = 0;				// set to initial value
	}
	
}
