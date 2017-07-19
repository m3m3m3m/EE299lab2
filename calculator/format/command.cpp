//----------------------------------------------------------------
//  Module name:
//      display.cpp
//  Languange:
//      C++
//  Description:
//      This header defines functions for commands used for i2c transfer,
//      including addCmd(), printErr(), printAns() and clear(), as well
//      as the event reciever.
//  Author:
//      Mingxiao An, Man Sun, Muhan Li
//  Rev.0 12 July 2017
//  Rev.1 13 July 2017
//  Rev.2 16 July 2017
//  Rev.3 17 July 2017
//----------------------------------------------------------------

#include "Arduino.h"
#include "Wire.h"
#include "../headers/constant.h"
#include "../headers/command.h"
#include "../headers/display.h"
#include "string.h"

namespace command {
    //-----------------------------------------------------------  
    // addCmd 
    //  
    // Purpose:  
    //    add one character to the remote lcd as input   
    // Parameters:  
    //    [in] char - the character to be sent to the remote lcd
    // Returns:  
    //    void  
    // Author:  
    //    Mingxiao An, Man Sun, Muhan Li
    //  Rev.0 12 July 2017
    //  Rev.1 13 July 2017
    //  Rev.2 16 July 2017
    //  Rev.3 17 July 2017
    //----------------------------------------------------------- 
    void addCmd(char cmd) {
        Wire.beginTransmission(I2C_PORT);   // start transmitting
        Wire.write(Command::ADDCMD);        // send the addcmd command
        Wire.write(cmd);                    // send the cmd to output
        Wire.endTransmission();             // stop transmitting
        Serial.print(cmd);                  // echo the output to monitor
    }

    //-----------------------------------------------------------  
    // printErr 
    //
    // Purpose:  
    //    send error information to the remote lcd
    // Parameters:  
    //    [in] char* - the char array (contains error info) to be 
    //                 sent to the remote lcd
    // Returns:  
    //    void  
    // Author:  
    //    Mingxiao An, Man Sun, Muhan Li
    //  Rev.0 12 July 2017
    //  Rev.1 13 July 2017
    //  Rev.2 16 July 2017
    //  Rev.3 17 July 2017
    //----------------------------------------------------------- 
    void printErr(char const* err) {
        Wire.beginTransmission(I2C_PORT);   // start transmitting
        Wire.write(Command::PRINTERR);      // send the printerr command
        Wire.write(err, strlen(err));       // send the error info
        Wire.endTransmission();             // stop transmitting
        Serial.println();
        Serial.println(err);                // echo the output to monitor
    }
    
    //-----------------------------------------------------------  
    // printAns 
    //  
    // Purpose:  
    //    send the result to the remote lcd 
    // Parameters:  
    //    [in] int - the result to be sent to the remote lcd  
    // Returns:  
    //    void  
    // Author:  
    //    Mingxiao An, Man Sun, Muhan Li
    //  Rev.0 12 July 2017
    //  Rev.1 13 July 2017
    //  Rev.2 16 July 2017
    //  Rev.3 17 July 2017
    //----------------------------------------------------------- 
    void printAns(int ans) {
        char buf[32];
        sprintf(buf, "%d", ans);
        Wire.beginTransmission(I2C_PORT);   // start transmitting
        Wire.write(Command::PRINTANS);      // send the printans command
        Wire.write(buf, strlen(buf));       // send the answer
        Wire.endTransmission();             // stop transmitting
        Serial.println(ans);                // echo the output to monitor
    }

    //-----------------------------------------------------------  
    // clear
    //  
    // Purpose:  
    //    clear and initialize the remote lcd
    // Parameters:  
    //    void
    // Returns:  
    //    void  
    // Author:  
    //    Mingxiao An, Man Sun, Muhan Li
    //  Rev.0 12 July 2017
    //  Rev.1 13 July 2017
    //  Rev.2 16 July 2017
    //  Rev.3 17 July 2017
    //----------------------------------------------------------- 
    void clear() {
        Wire.beginTransmission(I2C_PORT);   // start transmitting
        Wire.write(Command::CLEAR);         // send the clear command
        Wire.endTransmission();             // stop transmitting
    }

    //-----------------------------------------------------------  
    // receiveEvent
    //  
    // Purpose:  
    //    receive a command from a remote cmd and execute it, 
    //    registered as an event.
    // Parameters:  
    //    [in] int - the number of the bytes that need to be received,
    //               this input is managed by Wire.
    // Returns:  
    //    void  
    // Author:  
    //    Mingxiao An, Man Sun, Muhan Li
    //  Rev.0 12 July 2017
    //  Rev.1 13 July 2017
    //  Rev.2 16 July 2017
    //  Rev.3 17 July 2017
    //-----------------------------------------------------------
    // this function is registered as an event:
    void receiveEvent(int numBytes) {
        char ch;                            // input char from remote lcd
        char buf[32];                       // store the input command
        Command cmd = (Command)Wire.read(); // read the first char
        numBytes -= 1;                      // remained length decreased
        switch (cmd) {                      // recognize the command
            case Command::ADDCMD:           // display a char (1st row)
                ch = Wire.read();           // read one char from Wire
                display::addCmd(ch);        // display the char on lcd
                break;
            case Command::PRINTANS:         // display answer (2nd row)
            case Command::PRINTERR:         // display error (2nd row)
                for (int i = 0; i < numBytes; i++) {
                    buf[i] = Wire.read();   // read all the remaining 
                }                           // char one by one
                buf[numBytes] = '\0';       // add a null char in the end
                display::printErr(buf);     // display the error on lcd
                break;
            case Command::CLEAR:            // clear and initialize lcd
                display::clear();           // clear and initialize lcd
                break;
        }
    }
}
