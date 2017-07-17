//----------------------------------------------------------------
// Module name:
//    phase.h
// Languange:
//    C++
// Description:
//    This header provides options for different useages of this 
//	  module, including three demo phases.
// Author:
//	  Mingxiao An, Man Sun, Muhan Li
//	Rev.0 12 July 2017
//  Rev.1 13 July 2017
//  Rev.2 16 July 2017
//----------------------------------------------------------------
#ifndef PHASE_H
#define PHASE_H

namespace phase {

	namespace phase1 {
		void setup();
		void loop();
	}

	namespace phase2 {
		void setup();
		void loop();
	}

	namespace phase3 {
		void setup();
		void loop();
	}

	#if PHASE == 1

	using phase1::setup;
	using phase1::loop;

	#elif PHASE == 2

	using phase2::setup;
	using phase2::loop;

	#elif PHASE == 3

	using phase3::setup;
	using phase3::loop;

	#endif	// PHASE
}

#endif	// PHASE_H
