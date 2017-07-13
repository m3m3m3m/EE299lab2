
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
