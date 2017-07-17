//----------------------------------------------------------------
//  Module name:
//      phase1.cpp
//  Languange:
//      C++
//  Description:
//      The module implements the first phase in demo. It receives 
//      user input from serial monitor following the format of one 
//		digit, one operation symbol, one digit and one equality mark.
//		It will print the user input and result on the lcd screen.
//  Author:
//      Mingxiao An, Man Sun, Muhan Li
//  Rev.0 12 July 2017
//  Rev.1 13 July 2017
//  Rev.2 16 July 2017
//----------------------------------------------------------------
#include "Arduino.h"

#include "../headers/utils.h"
#include "../headers/display.h"
#include "../headers/constant.h"

namespace phase {			
	namespace phase1 {			// define the namespace of this phase
		int op_a;				// the fisrt input digit
		int op_b;				// the second input digit
		char opr;				// the input operation symbol
		int step = 0;			// the current input step (0,1,2,3)
 
		// the setup routine runs once when you press reset:
		void setup() {
			display::begin();	// set the display screen on a prepared state
			prompt();			// from utils.h, print hint for input
		}

		// declare functions used for propessing input in different steps
		int inputOpA();			
		int inputOpr();
		int inputOpB();
		int inputEqu();

		// the loop routine runs over and over again forever:
		void loop() {
			if (Serial.available() > 0) {
				switch(step) {
					case 0: step = inputOpA(); break;	// first input a digit
					case 1: step = inputOpr(); break;	// second input the operator
					case 2: step = inputOpB(); break;	// then input another digit
					case 3: step = inputEqu(); break;	// end with an equality mark
				}
				if (step == 0) {
					prompt();							// if a routine is over, start from the beginning
				}
			}
		}

		//-----------------------------------------------------------  
		// inputOpA 
		//  
		// Purpose:  
		//    recieve the first digit and check the validation
		// Parameters:  
		//    void 
		// Returns:  
		//    int - the next expected step   
		// Author:  
		//    Mingxiao An, Man Sun, Muhan Li
		//  Rev.0 12 July 2017
		//  Rev.1 13 July 2017
		//  Rev.2 16 July 2017
		//----------------------------------------------------------- 
		int inputOpA() {
			char incomingByte = Serial.read();			// read a byte from the serial monitor
/*?????*/	display::clear();// maybe move this to loop()->if(step == 0) {}
			if (isDigit(incomingByte)) {				// if the received byte is a digit (number 0 ~ 9)
				display::addCmd(incomingByte);			// display it on the lcd
				op_a = (int)(incomingByte - '0');		// save the byte as an integer
				return 1;								// wait for next step
			} else {									// if it is not a digit
				display::printErr("Invalid Digit");		// print error information
				return 0;								// wait for reinput of this round
			}
		}

		//-----------------------------------------------------------  
		// inputOpr 
		//  
		// Purpose:  
		//    recieve the operator and check the validation
		// Parameters:  
		//    void 
		// Returns:  
		//    int - the next expected step   
		// Author:  
		//    Mingxiao An, Man Sun, Muhan Li
		//  Rev.0 12 July 2017
		//  Rev.1 13 July 2017
		//  Rev.2 16 July 2017
		//----------------------------------------------------------- 
		int inputOpr() {
			char incomingByte = Serial.read();			// read a byte from the serial monitor
			if (isOpr(incomingByte)) {					// if the received byte is an operator ('+','-','*','/')
				display::addCmd(' ');
				display::addCmd(incomingByte);			// display it on the lcd
				opr = incomingByte;						// save the byte as a char
				return 2;								// wait for next step
			} else {									// if it is not an operator
				display::printErr("Invalid Operator");	// print error information
				return 0;								// wait for reinput of this round
			}
		}

		int inputOpB() {
			char incomingByte = Serial.read();			// read a byte from the serial monitor
			if (isDigit(incomingByte)) {				// if the received byte is a digit (number 0 ~ 9)
				display::addCmd(' ');
				display::addCmd(incomingByte);			// display it on the lcd
				op_b = (int)(incomingByte - '0');		// save the byte as an integer
				return 3;								// wait for next step
			} else {									// if it is not a digit
				display::printErr("Invalid Digit");		// print error information
				return 0;								// wait for reinput of this round
			}
		}

		int inputEqu() {
			char incomingByte = Serial.read();				// read a byte from the serial monitor
			if (incomingByte == '=') {						// if the received byte is an equality mark ('=')
				display::addCmd(' ');
				display::addCmd(incomingByte);				// display it on the lcd
				if (op_b == 0 && opr == '/') {				// if the calculation is invalid (divided by 0)
					display::printErr("Divided by Zero");	// print error information
					return 0;								// wait for reinput of this round
				} else {									// if input and calculation are both valid
/*ans*/				int ans = calc(op_a, op_b, opr);		// (clac() from utils.h) calculate the answer
					display::printAns(ans);					// display the answer			
					return 0;								// wait for a new round
				}
			} else {										// if the input is not '='
				display::printErr("Invalid Equ Sign");		// print error information
				return 0;									// wait for reinput of this round
			}
		}
	}
}
