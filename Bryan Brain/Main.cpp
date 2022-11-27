#include <ctime>    // time()

#include <iostream>
#include <chrono>

#include "Bryan.h"

/*
void testVirgo() {
    virgo::virgo_init();

    std::vector<uint16_t> legal_moves = {};

    virgo::Chessboard board = virgo::position_from_fen("rnbqkbnr/1pp1pppp/p7/3pP3/8/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 3");
    std::cout << board << std::endl;

    virgo::get_legal_moves<WHITE>(board, legal_moves);

    for (uint16_t& move : legal_moves) {
        std::cout << virgo::string::move_to_string(move) << std::endl;
    }

    std::cout << "\ntotal moves: " << legal_moves.size() << std::endl;
}
*/

void testBryan() {
    //srand((unsigned int)time(0));

    Bryan::Bryan bryan;

    auto a = std::chrono::high_resolution_clock::now();
    
    bryan.analyze();

    auto b = std::chrono::high_resolution_clock::now();
    std::cout << "took " << duration_cast<std::chrono::nanoseconds>(b - a).count() << " nanoseconds" << '\n';
    std::cout << "took " << duration_cast<std::chrono::microseconds>(b - a).count() << " microseconds" << '\n';
    std::cout << "took " << duration_cast<std::chrono::milliseconds>(b - a).count() << " milliseconds" << '\n';
    std::cout << "took " << duration_cast<std::chrono::seconds>(b - a).count() << " seconds" << '\n';
}

int main() {
    testBryan();
    
	return 0;
}
