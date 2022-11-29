#pragma once

#include <cstdint>
#include <unordered_set>
#include <map>

namespace Bryan {
	namespace Types {
		typedef std::uint64_t Bitboard;

		enum Piece {
			EMPTY,
			B_PAWN,
			B_KNIGHT,
			B_BISHOP,
			B_ROOK,
			B_QUEEN,
			B_KING,
			W_PAWN,
			W_KNIGHT,
			W_BISHOP,
			W_ROOK,
			W_QUEEN,
			W_KING
		};

		class Move {
		public:
			unsigned char from;
			unsigned char to;

			Move();
			Move(const std::uint8_t _from, const std::uint8_t _to);
		};
	}
}