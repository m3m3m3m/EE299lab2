//----------------------------------------------------------------
//  Module name:
//      display.h
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

#ifndef COMMAND_H
#define COMMAND_H

namespace command {
    enum Command {
        CLEAR, ADDCMD, PRINTERR, PRINTANS
    };

    void addCmd(char);          // add one character to the remote lcd as input 
    void printErr(char const*); // print error information to the remote lcd
    void printAns(int);         // print the result to the remote lcd 
    void clear();               // clear and initialize the remote lcd

    // this function is registered as an event:
    void receiveEvent(int);
}

#endif  // COMMAND_H
