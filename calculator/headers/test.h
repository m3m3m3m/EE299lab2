
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
