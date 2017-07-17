
#include "Arduino.h"

#include "../headers/utils.h"
#include "../headers/display.h"
#include "../headers/constant.h"

namespace phase {
	namespace phase3 {
		int op_a;
		int op_b;
		char opr;
		int step = 0;

		void setup() {
			display::begin();
			prompt();
		}

		int inputOpA();
		int inputOpr();
		int inputOpB();
		int inputEqu();

		void loop() {
			if (Serial.available() > 0) {
				switch(step) {
					case 0: step = inputOpA(); break;
					case 1: step = inputOpr(); break;
					case 2: step = inputOpB(); break;
					case 3: step = inputEqu(); break;
				}
				if (step == 0) {
					prompt();
				}
			}
		}

		int inputOpA() {
			display::clear();
			char bytes[3];
			int result = Serial.readBytes(bytes, 3);
			if (result == 2) {
				if (isDigit(bytes[0]) && isDigit(bytes[1])) {
					display::addCmd(bytes[0]);
					display::addCmd(bytes[1]);
					op_a = (int)(bytes[0] - '0') * 10 + (int)(bytes[1] - '0');
					return 1;
				} else {
					display::printErr("Invalid Digit");
					return 0;
				}
			} else if (result == 3) {
				if (bytes[0] == '-' && isDigit(bytes[1]) && isDigit(bytes[2])) {
					display::addCmd(bytes[0]);
					display::addCmd(bytes[1]);
					display::addCmd(bytes[2]);
					op_a = -(int)(bytes[1] - '0') * 10 - (int)(bytes[2] - '0');
					return 1;
				}
			} else {
				display::printErr("Invalid Input");
				return 0;
			}
		}

		int inputOpr() {
			char incomingByte = Serial.read();
			if (isOpr(incomingByte)) {
				display::addCmd(' ');
				display::addCmd(incomingByte);
				opr = incomingByte;
				return 2;
			} else {
				display::printErr("Invalid Operator");
				return 0;
			}
		}

		int inputOpA() {
			char bytes[3];
			int result = Serial.readBytes(bytes, 3);
			if (result == 2) {
				if (isDigit(bytes[0]) && isDigit(bytes[1])) {
					display::addCmd(bytes[0]);
					display::addCmd(bytes[1]);
					op_b = (int)(bytes[0] - '0') * 10 + (int)(bytes[1] - '0');
					return 3;
				} else {
					display::printErr("Invalid Digit");
					return 0;
				}
			} else if (result == 3) {
				if (bytes[0] == '-' && isDigit(bytes[1]) && isDigit(bytes[2])) {
					display::addCmd(bytes[0]);
					display::addCmd(bytes[1]);
					display::addCmd(bytes[2]);
					op_b = -(int)(bytes[1] - '0') * 10 - (int)(bytes[2] - '0');
					return 3;
				}
			} else {
				display::printErr("Invalid Input");
				return 0;
			}
		}

		int inputEqu() {
			char incomingByte = Serial.read();
			if (incomingByte == '=') {
				display::addCmd(' ');
				display::addCmd(incomingByte);
				if (op_b == 0 && opr == '/') {
					display::printErr("Divided by Zero");
					return 0;
				} else {
					int ans = calc(op_a, op_b, opr);
					display::printAns(ans);
					return 0;
				}
			} else {
				display::printErr("Invalid Equ Sign");
				return 0;
			}
		}
	}
}
