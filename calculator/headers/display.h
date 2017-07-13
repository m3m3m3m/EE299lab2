
#ifndef DISPLAY_H
#define DISPLAY_H

#include <LiquidCrystal.h>
#include "../headers/constant.h"

namespace display {
	void init();
	void addCmd(char);
	void printAns(char*);
	void clear();
}

#endif
