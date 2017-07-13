
#ifndef UTILS_H
#define UTILS_H

#include "Arduino.h"
#include "constant.h"

inline bool isDigit(char ch) {
	return ch >= '0' && ch <= '9';
}

inline bool isOpr(char ch) {
	return ch == '+' 
		|| ch == '-' 
		|| ch == '*' 
		|| ch == '/';
}

inline bool prompt() {
	#if PHASE == 0

	#else

	Serial.println("Please input the commands:");

	#endif	// PHASE
}

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
