#include "Position.h"

namespace Bryan {

	Position::Position() {
		for (std::uint8_t i = 0; i < 64; i++) {
			board[i] = Types::Piece::EMPTY;
		}
		whiteMove = true;
		castling = 0;
		enPassantSquare = 64;
		halfmoveClock = 0;
		fullmoveNumber = 1;
	}

	Position::Position(const std::string& fen) {
		set(fen);
	}
}