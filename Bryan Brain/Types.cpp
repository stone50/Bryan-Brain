#include "Types.h"

namespace Bryan {
	namespace Types {
		Move::Move() : from(0), to(0) {}

		Move::Move(const std::uint8_t _from, const std::uint8_t _to) : from(_from), to(_to) {}
	}
}