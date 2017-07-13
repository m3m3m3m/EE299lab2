
#include "Arduino.h"

#include "../headers/utils.h"
#include "../headers/display.h"
#include "../headers/constant.h"

namespace phase {
	namespace phase1 {
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

		int loop() {
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
			char incomingByte = Serial.read();
			display::clear();
			if (isDigit(incomingByte)) {
				display::addCmd(incomingByte);
				op_a = (int)(incomingByte - '0');
				return 1;
			} else {
				display::printErr("Invalid Digit");
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

		int inputOpB() {
			char incomingByte = Serial.read();
			if (isDigit(incomingByte)) {
				display::addCmd(' ');
				display::addCmd(incomingByte);
				op_b = (int)(incomingByte - '0');
				return 3;
			} else {
				display::printErr("Invalid Digit");
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
