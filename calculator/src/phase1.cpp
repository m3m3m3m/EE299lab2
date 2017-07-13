
#include "Arduino.h"
#include <LiquidCrystal.h>
#include "../headers/display.h"

namespace phase {
	namespace phase1 {

		int op_a,op_b,incomingByte = 0,crtstep = 0,res;
		int calc(int, int, char);
		char opr;
		void setup() {
		  // put your setup code here, to run once:
		  display::begin();
		  Serial.begin(9600);
		}

		void loop() {
		  // put your main code here, to run repeatedly:
		  if(Serial.available()>0){
			// read the incoming byte:
			incomingByte = Serial.read();
			switch(crtstep)
			{
			  case 0:
			  display::clear();
			  op_a = incomingByte-48;
			  Serial.print(op_a);
			  display::addCmd(op_a);
			  break;
			  case 1:
			  opr = (char) incomingByte;
			  Serial.print(opr);
			  display::addCmd(' ');
			  display::addCmd(opr);
			  break;
			  case 2:
			  op_b = incomingByte-48;
			  Serial.print(op_b);
			  display::addCmd(' ');
			  display::addCmd(op_b);
			  break;
			  case 3:
			  display::addCmd(' ');
			  display::addCmd('=');
			  if('/' == opr and op_b == 0)
			  {
				display::printAns("Divided by zero!");
				Serial.println("Divided by zero!");
			  }
			  else
			  {      
				res = calc(op_a,op_b,opr);
				Serial.print("=");
				Serial.println(res); 
				display::printAns(res);
			  }
			  break;
			}
			crtstep = crtstep + 1;
			if(4 == crtstep) crtstep = 0;
		  }
		}

		int calc(int a,int b,char op)
		{
		  int res = 0;
		  switch(op)
		  {
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
	}
}
