#include <cstdlib>
#include <ctime>

#include <iostream>

#define VIRGO_IMPLEMENTATION
#include "virgo.h"
#include "platform_folders.h"
#include "Utils.h"
#include "Brain.h"

const char PROJECT_NAME[] = "Bryan Brain";

int main() {
	srand((unsigned int)time(0));

	std::filesystem::path dataPath = sago::getDataHome();
	dataPath /= PROJECT_NAME;
	std::cout << dataPath << '\n';
    std::cout << dataPath / "Test Brain.brain" << '\n';

    Brain testBrain = Brain(5, 5, 5);
    testBrain.randomize();
    testBrain.save(dataPath / "Test Brain.brain");
    Brain::load(dataPath / "Test Brain.brain", testBrain);

    virgo::virgo_init();

    std::vector<uint16_t> legal_moves = {};

    virgo::Chessboard board = virgo::position_from_fen("rnbqkbnr/1pp1pppp/p7/3pP3/8/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 3");
    std::cout << board << std::endl;

    virgo::get_legal_moves<WHITE>(board, legal_moves);

    for (uint16_t& move : legal_moves) {
        std::cout << virgo::string::move_to_string(move) << std::endl;
    }

    std::cout << "\ntotal moves: " << legal_moves.size() << std::endl;

	return 0;
}
