#include "Arduino.h"
#include <LiquidCrystal.h>
namespace phase {
	namespace phase1 {
		LiquidCrystal lcd(2, 3, 4, 5, 6, 7, 8);     // Bus 1 of the Seeduino sensor Chasis
		int op_a,op_b,incomingByte = 0,crtstep = 0,res;
		char opr;
		void setup() {
		  // put your setup code here, to run once:
		  lcd.begin(16, 2);
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
			  lcd.clear();
			  lcd.setCursor(5,0);
			  op_a = incomingByte-48;
			  Serial.print(op_a);
			  lcd.print(op_a);
			  break;
			  case 1:
			  opr = (char) incomingByte;
			  Serial.print(opr);
			  lcd.print(' ');
			  lcd.print(opr);
			  break;
			  case 2:
			  op_b = incomingByte-48;
			  Serial.print(op_b);
			  lcd.print(' ');
			  lcd.print(op_b);
			  break;
			  case 3:
			  lcd.print(" =");
			  lcd.setCursor(0, 1);
			  if('/' == opr and op_b == 0)
			  {
				lcd.print("Divided by zero!");
				Serial.println("Divided by zero!");
			  }
			  else
			  {      
				res = calc(op_a,op_b,opr);
				Serial.print("=");
				Serial.println(res); 
				lcd.setCursor(7,1);
				lcd.print(res);
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
