#include "Bryan.h"

namespace Bryan {
	bool Bryan::save() {
		return brain.save(projectDataLocation / name);
	}

	bool Bryan::load() {
		return Brain::load(projectDataLocation / name, brain);
	}
}