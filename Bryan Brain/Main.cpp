#include <ctime>    // time()

#include <iostream>
#include <chrono>

#include "Bryan.h"

void testBryan() {
    //srand((unsigned int)time(0));

    Bryan::Bryan bryan;

    bryan.setPosition("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    Bryan::Position position = bryan.getPosition();

    std::cout << "Board:" << '\n';
    for (int i = 0; i < 64; i++) {
        std::cout << Bryan::Data::PIECE_CHAR.at(position.getPieceAt(i));
        if (i % 8 == 7) {
            std::cout << '\n';
        }
    }

    std::cout << "White To Move: " << position.getWhiteMove() << '\n';
    std::cout << "White Can Castle King's Side: " << position.whiteCanCastleKing() << '\n';
    std::cout << "White Can Castle Queen's Side: " << position.whiteCanCastleQueen() << '\n';
    std::cout << "Black Can Castle King's Side: " << position.blackCanCastleKing() << '\n';
    std::cout << "Black Can Castle Queen's Side: " << position.blackCanCastleQueen() << '\n';
    std::cout << "En Passant Square: " << (int)position.getEnPassantSquare() << '\n';
    std::cout << "Halfmove Clock: " << (int)position.getHalfmoveClock() << '\n';
    std::cout << "Fullmove Number: " << (int)position.getFullmoveNumber() << '\n';

    //auto a = std::chrono::high_resolution_clock::now();
    
    //bryan.analyze();

    //auto b = std::chrono::high_resolution_clock::now();
    //std::cout << "took " << duration_cast<std::chrono::nanoseconds>(b - a).count() << " nanoseconds" << '\n';
    //std::cout << "took " << duration_cast<std::chrono::microseconds>(b - a).count() << " microseconds" << '\n';
    //std::cout << "took " << duration_cast<std::chrono::milliseconds>(b - a).count() << " milliseconds" << '\n';
    //std::cout << "took " << duration_cast<std::chrono::seconds>(b - a).count() << " seconds" << '\n';
}

int main() {
    testBryan();
    
	return 0;
}