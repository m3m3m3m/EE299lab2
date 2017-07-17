//----------------------------------------------------------------
//	Module name:
//		display.cpp
//	Languange:
//		C++
//	Description:
//		This header defines functions for commands used for i2c transfer,
//		including addCmd(), printErr(), printAns() and clear(), as well
//		as the event reciever.
//	Author:
//		Mingxiao An, Man Sun, Muhan Li
//	Rev.0 12 July 2017
//	Rev.1 13 July 2017
//	Rev.2 16 July 2017
//	Rev.3 17 July 2017
//----------------------------------------------------------------

#include "Arduino.h"
#include "Wire.h"
#include "../headers/constant.h"
#include "../headers/command.h"
#include "../headers/display.h"
#include "string.h"

namespace command {
	// add one character to the remote lcd as input
	void addCmd(char cmd) {
		Wire.beginTransmission(I2C_PORT);	// start transmitting
    	Wire.write(Command::ADDCMD);   		// send the addcmd command
    	Wire.write(cmd);					// send the cmd to output
    	Wire.endTransmission();         	// stop transmitting
    	Serial.print(cmd);					// echo the output to monitor
	}

	// print error information to the remote lcd:
	void printErr(char const* err) {
		Wire.beginTransmission(I2C_PORT);	// start transmitting
    	Wire.write(Command::PRINTERR);   	// send the printerr command
    	Wire.write(err, strlen(err));		// send the error info
    	Wire.endTransmission();         	// stop transmitting
    	Serial.println();
    	Serial.println(err);				// echo the output to monitor
	}
	
	// print the result to the remote lcd 
	void printAns(int ans) {
		char buf[32];
		sprintf(buf, "%d", ans);
		Wire.beginTransmission(I2C_PORT);	// start transmitting
    	Wire.write(Command::PRINTANS);		// send the printans command
    	Wire.write(buf, strlen(buf));		// send the answer
    	Wire.endTransmission();         	// stop transmitting
    	Serial.println(ans);				// echo the output to monitor
	}

	// clear and initialize the remote lcd
	void clear() {
		Wire.beginTransmission(I2C_PORT);	// start transmitting
    	Wire.write(Command::CLEAR);   		// send the clear command
    	// Serial.println('write');
    	Wire.endTransmission();         	// stop transmitting
    	// Serial.println("endTransmission");
	}

	// this function is registered as an event:
	void receiveEvent(int numBytes) {
		char ch;
		char buf[32];
		Command cmd = (Command)Wire.read();
		numBytes -= 1;
		switch (cmd) {
			case Command::ADDCMD:
				ch = Wire.read();
				display::addCmd(ch);
				break;
			case Command::PRINTANS:
			case Command::PRINTERR:
				for (int i = 0; i < numBytes; i++) {
					buf[i] = Wire.read();
				}
				buf[numBytes] = '\0';
				display::printErr(buf);
				break;
			case Command::CLEAR:
				display::clear();
				break;
		}
	}
}
