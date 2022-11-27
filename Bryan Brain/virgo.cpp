#include "virgo.h"

namespace virgo {
    // Default constructor which initializes to the initial chess configuration
    Chessboard::Chessboard() {
        // Initial chessboard setup
        this->castling_perm = 0x00;
        this->fifty_mv_counter = 0;
        this->next = WHITE;
        this->enpassant = INVALID;
        this->king_position[0] = e8;
        this->king_position[1] = e1;

        // Set chess starting position
        this->all = 0xffff00000000ffff;

        // Set black pieces
        this->pieces[0][PAWN] = 0x00ff000000000000; // Pawns
        this->pieces[0][ROOK] = 0x8100000000000000; // Rooks
        this->pieces[0][KNIGHT] = 0x4200000000000000; // Knights
        this->pieces[0][BISHOP] = 0x2400000000000000; // Bishops
        this->pieces[0][KING] = 0x0800000000000000; // King
        this->pieces[0][QUEEN] = 0x1000000000000000; // Queen

        // Set white pieces
        this->pieces[1][PAWN] = 0x000000000000ff00; // Pawns
        this->pieces[1][ROOK] = 0x0000000000000081; // Rooks
        this->pieces[1][KNIGHT] = 0x0000000000000042; // Knights
        this->pieces[1][BISHOP] = 0x0000000000000024; // Bishops
        this->pieces[1][KING] = 0x0000000000000008; // King
        this->pieces[1][QUEEN] = 0x0000000000000010; // Queen

        // Fill with empty values
        for (int s = a1; s <= h8; s++) {
            this->squares[s] = std::make_pair(EMPTY, BLACK);
        }

        // Set every pair which has a piece on the corresponding square index
        for (int i = PAWN; i <= QUEEN; i++) {
            uint64_t board = this->pieces[BLACK][i];
            while (board) {
                this->squares[bit::pop_lsb_index(board)] = std::make_pair(static_cast<Piece>(i), BLACK);
                board &= (board - 1);
            }
            board = this->pieces[WHITE][i];
            while (board) {
                this->squares[bit::pop_lsb_index(board)] = std::make_pair(static_cast<Piece>(i), WHITE);
                board &= (board - 1);
            }
        }
    }

    // Copy constructor
    Chessboard::Chessboard(Chessboard const& c) {
        this->all = c.all;
        this->castling_perm = c.castling_perm;
        this->fifty_mv_counter = c.fifty_mv_counter;
        this->next = c.next;
        this->enpassant = c.enpassant;

        memcpy(this->pieces, c.pieces, 12 * sizeof(uint64_t));

        for (int s = a1; s <= h8; s++) {
            this->squares[s] = c.squares[s];
        }

        this->king_position[0] = c.king_position[0];
        this->king_position[1] = c.king_position[1];
    }
}