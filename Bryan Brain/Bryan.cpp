#include "Bryan.h"

namespace Bryan {
	Bryan::Bryan() :
		name("Bryan"),
		stateInfo(),
		brain(Brain(67, 100, 1885)),
		position(),
		moveEvals()
	{}

	Bryan::Bryan(const std::string& name, const std::string& fen) :
		name(name),
		stateInfo(),
		brain(Brain(67, 100, 1885)),
		position(),
		moveEvals()
	{
		setPosition(fen);
	}

	bool Bryan::save() {
		return brain.save(projectDataLocation / name);
	}

	bool Bryan::load() {
		return Brain::load(projectDataLocation / name, brain);
	}
}