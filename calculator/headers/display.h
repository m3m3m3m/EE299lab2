
#ifndef DISPLAY_H
#define DISPLAY_H

#include <LiquidCrystal.h>
#include "../headers/constant.h"

namespace display {
	void begin();
	void addCmd(char);
	void addCmd(int);
	void printAns(char const*);
	void printAns(int);
	void clear();
}

#endif
