#pragma once

#include <string>
#include <vector>

#include <iostream>

#include "Bitboards.h"
#include "Data.h"

namespace Bryan {
	class Position {
	private:

		Types::Piece board[64];

		bool whiteMove;

		// first 4 bits indicate castling abilities
		// 00001000 = white king side
		// 000001000 = white queen side
		// 00000010 = black king side
		// 000000001 = black queen side
		std::uint8_t castling;

		// index 0-63, 64 if no en passant square
		unsigned char enPassantSquare;

		unsigned char halfmoveClock;

		unsigned char fullmoveNumber;
		
	public:

		Position();
		Position(const std::string& fen);

		inline void set(const std::string& fen) {
			std::uint8_t boardIndex = 0;
			std::uint8_t i = -1;
			while (fen[++i] != ' ') {
				if (isdigit(fen[i])) {
					std::uint8_t emptyCount = fen[i] - 48;
					while (emptyCount-- > 0) {
						board[boardIndex++] = Types::Piece::EMPTY;
					}
				}
				else if (fen[i] != '/') {
					board[boardIndex++] = Data::CHAR_PIECE.at(fen[i]);
				}
			}
			i++;
			whiteMove = (fen[i++] == 'w');
			i++;

			castling = 0;
			castling = (castling + (fen[i++] == 'K')) << 1;
			castling = (castling + (fen[i++] == 'Q')) << 1;
			castling = (castling + (fen[i++] == 'k')) << 1;
			castling = (castling + (fen[i++] == 'q'));
			i++;

			if (fen[i] != '-') {
				enPassantSquare = (fen[i++] - 97) * 8;
				enPassantSquare += fen[i++] - 49;
			}
			else {
				enPassantSquare = 64;
				i++;
			}

			halfmoveClock = 0;
			while (fen[++i] != ' ') {
				halfmoveClock *= 10;
				halfmoveClock += fen[i] - 48;
			}

			fullmoveNumber = 0;
			while (++i < fen.size()) {
				fullmoveNumber *= 10;
				fullmoveNumber += fen[i] - 48;
			}
		}

		inline Types::Piece getPieceAt(const unsigned char index) {
			return board[index];
		}

		inline bool getWhiteMove() {
			return whiteMove;
		}

		inline bool whiteCanCastleKing() {
			return castling & 8;
		}

		inline bool whiteCanCastleQueen() {
			return castling & 4;
		}

		inline bool blackCanCastleKing() {
			return castling & 2;
		}

		inline bool blackCanCastleQueen() {
			return castling & 1;
		}

		inline unsigned char getEnPassantSquare() {
			return enPassantSquare;
		}

		inline unsigned char getHalfmoveClock() {
			return halfmoveClock;
		}

		inline unsigned char getFullmoveNumber() {
			return fullmoveNumber;
		}
	};
}