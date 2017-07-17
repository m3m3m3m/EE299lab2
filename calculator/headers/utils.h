//----------------------------------------------------------------
// 	Module name:
//    	utils.h
// 	Languange:
//    	C++
// 	Description:
//    	This header provides many useful tools for this module,
//	  	including judging validility, printing hint and doing
//	  	calculations.
// 	Author:
//	  	Mingxiao An, Man Sun, Muhan Li
//	Rev.0 12 July 2017
//  Rev.1 13 July 2017
//  Rev.2 16 July 2017
//----------------------------------------------------------------
#ifndef UTILS_H
#define UTILS_H

#include "Arduino.h"
#include "constant.h"

//-----------------------------------------------------------  
// isDigit
//  
// Purpose:  
//    judge if the input char is a digit number ('0' ~ '9')
// Parameters:  
//    [in] char - the character to be judged
// Returns:  
//    bool - whether the input char is a digit  
// Author:  
//    Mingxiao An, Man Sun, Muhan Li
//  Rev.0 12 July 2017
//-----------------------------------------------------------  
inline bool isDigit(char ch) {
	return ch >= '0' && ch <= '9';
}

//-----------------------------------------------------------  
// isOpr
//  
// Purpose:  
//    judge if the input char is an operator('+','-','*','/')
// Parameters:  
//    [in] char - the character to be judged
// Returns:  
//    bool - whether the input char is an operator 
// Author:  
//    Mingxiao An, Man Sun, Muhan Li
//  Rev.0 12 July 2017
//-----------------------------------------------------------
inline bool isOpr(char ch) {
	return ch == '+' 
		|| ch == '-' 
		|| ch == '*' 
		|| ch == '/';
}

//-----------------------------------------------------------  
// prompt
//  
// Purpose:  
//    print the hint on serial monitor for users
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
inline bool prompt() {
	#if PHASE == 0

	#else

	Serial.println("Please input the commands:");

	#endif	// PHASE
}

//-----------------------------------------------------------  
// calc
//  
// Purpose:  
//    calculate according to the input numbers and operators
// Parameters:  
//    [in] int - the input operand (first)
//	  [in] int - the input operand (second)
//	  [in] char - the operator
//		
// Returns:  
//    int - the calculation result
// Author:  
//    Mingxiao An, Man Sun, Muhan Li
//  Rev.0 12 July 2017
//  Rev.1 13 July 2017
//  Rev.2 16 July 2017
//-----------------------------------------------------------
inline int calc(int a, int b, char op) {
	int res = 0;
	switch(op) {
		case '+':
			res = a + b;
			break;
		case '-':
			res = a - b;
			break;
		case '*':
			res = a * b;
			break;
		case '/':
			res = a / b;
			break;
	}
	return res;
}

#endif	// UTILS_H
