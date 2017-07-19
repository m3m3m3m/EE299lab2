//----------------------------------------------------------------
//  Module name:
//      phase1.cpp
//  Languange:
//      C++
//  Description:
//      The module implements the forth phase in demo. The master
//      gets input and controls the slave to output based on the
//      third phase.
//  Author:
//      Mingxiao An, Man Sun, Muhan Li
//  Rev.0 12 July 2017
//  Rev.1 13 July 2017
//  Rev.2 16 July 2017
//  Rev.3 17 July 2017
//----------------------------------------------------------------

#include "Arduino.h"
#include "Wire.h"

#include "../headers/utils.h"
#include "../headers/command.h"
#include "../headers/display.h"
#include "../headers/constant.h"

namespace phase {   
    namespace phase4 {
    
        #if MASTER == 1

        // the setup routine runs once when you press reset:
        void setup() {
            Wire.begin();
            prompt();
        }

        int op_a;                   // the fisrt input number
        int op_b;                   // the second input number
        char opr;                   // the input operation symbol
        int step = 0;               // the current input step (0,1,2,3)

        // declare functions used for propessing input in different steps
        int inputOpA();
        int inputOpr();
        int inputOpB();
        int inputEqu();

        // the loop routine runs over and over again forever:
        void loop() {
            if (Serial.available() > 0) {
                switch(step) {      
                    case 0:         // first input a signed number of 2 digits
                        step = inputOpA(); 
                        break;  
                    case 1:         // second input the operator
                        step = inputOpr(); 
                        break;  
                    case 2:         // then input another 2-digit signed number
                        step = inputOpB(); 
                        break;  
                    case 3:         // end with an equality mark
                        step = inputEqu(); 
                        break;  
                }
                if (step == 0) {    // start from the beginning
                    prompt();
                }
            }
        }

        //-----------------------------------------------------------  
        // inputOpA 
        //  
        // Purpose:  
        //    recieve the signed first 2-digit number and check the 
        //    validation
        // Parameters:  
        //    void 
        // Returns:  
        //    int - the next expected step   
        // Author:  
        //    Mingxiao An, Man Sun, Muhan Li
        //  Rev.0 12 July 2017
        //  Rev.1 13 July 2017
        //  Rev.2 16 July 2017
        //  Rev.3 17 July 2017
        //-----------------------------------------------------------
        int inputOpA() {
            command::clear();
            char bytes[3];          // define a buffer to store the input
            // receive the input from serial monitor into the buffer
            int result = Serial.readBytes(bytes, 3);
            if (result == 2) {      // if the input is 2-digit
                // if the input is a positive number
                if (isDigit(bytes[0]) && isDigit(bytes[1])) {
                    // print the number on the remote lcd
                    command::addCmd(bytes[0]);
                    command::addCmd(bytes[1]);
                    // transfer the 3-digit buffer into a number
                    op_a = (int)(bytes[0] - '0') * 10 + (int)(bytes[1] - '0');
                    return 1;       // wait for next step
                } else {            // if invalid
                    // print error information
                    command::printErr("Invalid Digit");
                    // wait for reinput of this round
                    return 0;
                }
            } else if (result == 3) {// if the input is 3-digit
                // if the input is a negative number
                if (bytes[0] == '-' && isDigit(bytes[1]) && isDigit(bytes[2])) {
                    // print the number on the remote lcd
                    command::addCmd(bytes[0]);
                    command::addCmd(bytes[1]);
                    command::addCmd(bytes[2]);
                    // transfer the 3-digit buffer into a number
                    op_a = -(int)(bytes[1] - '0') * 10 - (int)(bytes[2] - '0');
                    return 1;       // wait for next step
                }
            } else {                // if invalid
                // print error information
                command::printErr("Invalid Input");
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
        //  Rev.3 17 July 2017
        //-----------------------------------------------------------
        int inputOpr() {
            // read a byte from the serial monitor
            char incomingByte = Serial.read();
            // if the received byte is an operator
            if (isOpr(incomingByte)) {
                command::addCmd(' ');
                command::addCmd(incomingByte);  // display it on the remote lcd
                opr = incomingByte;             // save the byte as a char
                return 2;                       // wait for next step
            } else {                            // if it is not an operator
                // print error information
                command::printErr("Invalid Operator");
                // wait for reinput of this round
                return 0;
            }
        }

        //-----------------------------------------------------------  
        // inputOpB 
        //  
        // Purpose:  
        //    recieve the signed second 2-digit number and check the validation
        // Parameters:  
        //    void 
        // Returns:  
        //    int - the next expected step   
        // Author:  
        //    Mingxiao An, Man Sun, Muhan Li
        //  Rev.0 12 July 2017
        //  Rev.1 13 July 2017
        //  Rev.2 16 July 2017
        //  Rev.3 17 July 2017
        //-----------------------------------------------------------
        int inputOpB() {
            char bytes[3];          // define a buffer to store the input
            // receive the input from serial monitor into the buffer
            int result = Serial.readBytes(bytes, 3);
            if (result == 2) {
                // if the input is a positive number
                if (isDigit(bytes[0]) && isDigit(bytes[1])) {
                    // print the number on the remote lcd
                    command::addCmd(' ');
                    command::addCmd(bytes[0]);
                    command::addCmd(bytes[1]);
                    // transfer the 3-digit buffer into a number
                    op_b = (int)(bytes[0] - '0') * 10 + (int)(bytes[1] - '0');
                    return 3;       // wait for next step
                } else {
                    // print error information
                    command::printErr("Invalid Digit");
                    // wait for reinput of this round
                    return 0;
                }
            } else if (result == 3) {
                // if the input is a negative number
                if (bytes[0] == '-' && isDigit(bytes[1]) && isDigit(bytes[2])) {
                    // print the number on the remote lcd
                    command::addCmd(' ');
                    command::addCmd(bytes[0]);
                    command::addCmd(bytes[1]);
                    command::addCmd(bytes[2]);
                    // transfer the 3-digit buffer into a number
                    op_b = -(int)(bytes[1] - '0') * 10 - (int)(bytes[2] - '0');
                    return 3;       // wait for next step
                }
            } else {
                // print error information
                command::printErr("Invalid Input");
                // wait for reinput of this round
                return 0;
            }
        }

        //-----------------------------------------------------------  
        // inputEqu 
        //  
        // Purpose:  
        //    recieve the equality mark, check the validation and calc-
        //    ulate the result
        // Parameters:  
        //    void 
        // Returns:  
        //    int - the next expected step   
        // Author:  
        //    Mingxiao An, Man Sun, Muhan Li
        //  Rev.0 12 July 2017
        //  Rev.1 13 July 2017
        //  Rev.2 16 July 2017
        //  Rev.3 17 July 2017
        //----------------------------------------------------------- 
        int inputEqu() {
            // read a byte from the serial monitor
            char incomingByte = Serial.read();
            // if the received byte is an equality mark ('=')
            if (incomingByte == '=') {
                command::addCmd(' ');
                command::addCmd(incomingByte);  // display it on the remote lcd
                if (op_b == 0 && opr == '/') {
                    // print error information
                    command::printErr("Divided by Zero");
                    // wait for reinput of this round
                    return 0;
                } else {    // if input and calculation are both valid
                    // (clac() from utils.h) calculate the answer
                    int ans = calc(op_a, op_b, opr);
                    command::printAns(ans);     // display the answer
                    return 0;                   // wait for a new round
                }
            } else {                            // if the input is not '='
                // print error information
                command::printErr("Invalid Equ Sign");
                // wait for reinput of this round
                return 0;
            }
        }
        

        #else

        // the setup routine runs once when you press reset:
        void setup() {
            display::begin();
            Wire.begin(I2C_PORT);                   // join i2c bus
            Wire.onReceive(command::receiveEvent);  // register event
            Serial.println("finished setup");       // print the hint   
        }

        // the loop routine runs over and over again forever:
        void loop() {
            delay(100);
        }

        #endif  // MASTER
    }
}

