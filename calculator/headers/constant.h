//----------------------------------------------------------------
//  Module name:
//      constant.h
//  Languange:
//      C++
//  Description:
//      This header defines constants used in the program, such us
//		pin numbers, baud rate, and other constant values.
//  Author:
//  	Rev.0 12 July 2017 by Mingxiao An
//----------------------------------------------------------------

#ifndef CONSTANT_H
#define CONSTANT_H

#define BAUD_RATE 	9600				// baud rate for serial monitor
#define LCD_PORT 	2, 3, 4, 5, 6, 7, 8	// bus 1 of the Seeduino sensor Chasis
#define I2C_PORT 	4					// analog port for i2c bus
#define PHASE		0					// when phase is 0, the code goes to test
#define TEST 		1					// the test code No.

#endif	// CONSTANT_H
