/*
  Stockfish, a UCI chess playing engine derived from Glaurung 2.1
  Copyright (C) 2004-2022 The Stockfish developers (see AUTHORS file)

  Stockfish is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Stockfish is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>

#include <chrono>

#include "Stockfish/bitboard.h"
#include "Stockfish/endgame.h"
#include "Stockfish/position.h"
#include "Stockfish/psqt.h"
#include "search.h"
#include "Stockfish/syzygy/tbprobe.h"
#include "Stockfish/thread.h"
#include "Stockfish/tt.h"
#include "Stockfish/uci.h"
#include "bryan.h"

using namespace Stockfish;

void printMove(const Move& move) {
	std::cout << UCI::square(from_sq(move)) << UCI::square(to_sq(move)) << type_of(move) << promotion_type(move) << '\n';
}

void initStockfish(int argc, char* argv[]) {
	std::cout << engine_info() << std::endl;
	//CommandLine::init(argc, argv);
	UCI::init(Options);
	//Tune::init();
	//PSQT::init();
	Bitboards::init();
	//Position::init();
	//Bitbases::init();
	//Endgames::init();
	//Threads.set(size_t(Options["Threads"]));
	Threads.set(1);
	//Search::clear(); // After threads are up
	//Eval::NNUE::init();

	//UCI::loop(argc, argv);
}

int main(int argc, char* argv[]) {
  initStockfish(argc, argv);

  Bryan::Bryan bryan;
  bryan.setPosition("rnbqkb1r/ppp2ppp/5n2/3pp3/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 0 4");

  const unsigned int ANALYZE_COUNT = 10;

  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();

  for (int i = 0; i < ANALYZE_COUNT; i++) {
	  bryan.analyze();
  }

  end = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsed_seconds = end - start;
  std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
  std::cout << "average time per analysis: " << elapsed_seconds.count() / ANALYZE_COUNT << "s/a\n";
  std::cout << bryan.getMoveEvals().size() << "\n";

  Threads.set(0);

  return 0;
}
