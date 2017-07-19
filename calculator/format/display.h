//----------------------------------------------------------------
//  Module name:
//      display.h
//  Languange:
//      C++
//  Description:
//      This header defines functions for display used in the program,
//      including begin(), addCmd(), printErr(), printAns() and clear().
//  Author:
//      Mingxiao An, Man Sun, Muhan Li
//  Rev.0 12 July 2017
//  Rev.1 13 July 2017
//  Rev.2 16 July 2017
//----------------------------------------------------------------
#ifndef DISPLAY_H
#define DISPLAY_H

#include <LiquidCrystal.h>
#include "../headers/constant.h"

namespace display {
    void begin();               // initialize some local variables and prepare for the display
    void addCmd(char);          // add one character to the lcd as input 
    void printErr(char const*); // print error information on the lcd
    void printAns(int);         // print the result of calculation on lcd 
    void clear();               // clear all the content on lcd and set to the initial state 
}

#endif
