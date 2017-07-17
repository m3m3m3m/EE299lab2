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
			display::begin();	// set the lcd on a prepared state
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
					case 0: 				// first input a digit
						step = inputOpA(); 
						break;
					case 1: 				// second input the operator
						step = inputOpr(); 
						break;
					case 2: 				// then input another digit
						step = inputOpB(); 
						break;
					case 3: 				// end with an equality mark
						step = inputEqu(); 
						break;				
				}
				if (step == 0) {			// start from the beginning
					prompt();		
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
			// read a byte from the serial monitor
			char incomingByte = Serial.read();
			display::clear();
			// if the received byte is a digit (number 0 ~ 9)
			if (isDigit(incomingByte)) {				
				display::addCmd(incomingByte);	// display it on the lcd
				// save the byte as an integer
				op_a = (int)(incomingByte - '0');		
				return 1;						// wait for next step
			} else {							// if it is not a digit
				// print error information
				display::printErr("Invalid Digit");		
				// wait for reinput of this round
				return 0;						
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
			// read a byte from the serial monitor
			char incomingByte = Serial.read();			
			// if the received byte is an operator
			if (isOpr(incomingByte)) {					
				display::addCmd(' ');
				display::addCmd(incomingByte);	// display it on the lcd
				opr = incomingByte;				// save the byte as a char
				return 2;						// wait for next step
			} else {							// if it is not an operator
				// print error information
				display::printErr("Invalid Operator");	
				// wait for reinput of this round
				return 0;							
			}
		}

		//-----------------------------------------------------------  
		// inputOpB 
		//  
		// Purpose:  
		//    recieve the second digit and check the validation
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
		int inputOpB() {
			// read a byte from the serial monitor
			char incomingByte = Serial.read();	
			// if the received byte is a digit (number 0 ~ 9)		
			if (isDigit(incomingByte)) {				
				display::addCmd(' ');
				display::addCmd(incomingByte);	// display it on the lcd
				// save the byte as an integer
				op_b = (int)(incomingByte - '0');		
				return 3;						// wait for next step
			} else {							// if it is not a digit
				// print error information
				display::printErr("Invalid Digit");	
				// wait for reinput of this round	
				return 0;						
			}
		}

		//-----------------------------------------------------------  
		// inputEqu 
		//  
		// Purpose:  
		//    recieve the equality mark, check the validation and calc-
		//	  ulate the result
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
		int inputEqu() {
			// read a byte from the serial monitor
			char incomingByte = Serial.read();
			// if the received byte is an equality mark ('=')				
			if (incomingByte == '=') {						
				display::addCmd(' ');
				display::addCmd(incomingByte);	// display it on the lcd
				// if the calculation is invalid (divided by 0)
				if (op_b == 0 && opr == '/') {	
					// print error information			
					display::printErr("Divided by Zero");	
					// wait for reinput of this round
					return 0;					
				} else {	// if input and calculation are both valid
					// (clac() from utils.h) calculate the answer
					int ans = calc(op_a, op_b, opr);		
					display::printAns(ans);		// display the answer			
					return 0;					// wait for a new round
				}
			} else {							// if the input is not '='
				// print error information
				display::printErr("Invalid Equ Sign");	
				// wait for reinput of this round	
				return 0;									
			}
		}
	}
}
