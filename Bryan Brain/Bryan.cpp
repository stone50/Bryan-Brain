#include "Bryan.h"

namespace Bryan {
	bool Bryan::save() {
		return brain.save(brainLocation / name);
	}

	bool Bryan::load() {
		return Brain::load(brainLocation / name, brain);
	}
}