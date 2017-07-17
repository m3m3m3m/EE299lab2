//----------------------------------------------------------------
// Module name:
//    test.h
// Languange:
//    C++
// Description:
//    This header defines namespace for testing of this module.
// Author:
//	  Mingxiao An, Man Sun, Muhan Li
//	Rev.0 12 July 2017
//  Rev.1 13 July 2017
//  Rev.2 16 July 2017
//----------------------------------------------------------------
#ifndef TEST_H
#define TEST_H

#include "../headers/constant.h"

namespace test {
	
	namespace display {
		void setup();
		void loop();
	}

	#if TEST == 1
	
	using display::setup;
	using display::loop;
	
	#endif	// TEST
}

#endif	// TEST_H
