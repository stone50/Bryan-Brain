#pragma once

#include <unordered_set>

#include "Stockfish/position.h"
#include "Stockfish/movegen.h"
#include "Brain.h"

namespace Bryan {
    class Bryan {
    public:

        struct MoveEval {
            Stockfish::Move move;
            float eval;
        };

        std::string name;
        
        Bryan();

        Bryan(const std::string& name, const std::string& fen);

        inline void analyze() {
            setInputs();

            brain.think();

            generateMoveEvals();
        }

        inline void resetBrainState() {
            brain.resetState();
        }

        inline void randomizeBrain() {
            srand(time(0));
            brain.randomize();
        }

        inline void setPosition(const std::string& fen) {
            position.set(fen, false, &stateInfo, position.this_thread());
        }

        bool save();

        bool load();

        inline float getEval() {
            return brain.getOutput(1858);
        }

        inline Brain getBrain() {
            return brain;
        }

        inline const Stockfish::Position& getPosition() {
            return position;
        }

        inline std::vector<MoveEval> getMoveEvals() {
            return moveEvals;
        }

    private:

        Stockfish::StateInfo stateInfo;

        const std::filesystem::path projectDataLocation = Utils::DATA_PATH / "Bryan";

        /*
        inputs =
        8 x 8 = 64 - piece placement data
        1 - active color
        1 - castling availability
        1 - en passant target square
        = 67

        middles =
        ???
        = ?

        outputs =
        1 - evaluation
        1884 - all possible moves (see Utils::MOVE_LIST)
        = 1885
        */
        Brain brain;

        Stockfish::Position position;

        std::vector<MoveEval> moveEvals;

        inline void setInputs() {
            // piece placement data
            for (unsigned char i = 0; i < 64; i++) {
                brain.setInput(i, static_cast<float>(position.piece_on(Stockfish::Square(i))));
            }

            // active color
            brain.setInput(64, static_cast<float>(position.side_to_move()));
            
            // castling availability
            brain.setInput(65, static_cast<float>((position.castling_rights(Stockfish::WHITE) << 4) + position.castling_rights(Stockfish::BLACK)));

            // en passant target square
            brain.setInput(66, static_cast<float>(position.ep_square()));
        }

        inline std::unordered_set<Stockfish::Move> getLegalMoves() {
            Stockfish::MoveList<Stockfish::LEGAL> legalMovesList(position);

            std::unordered_set<Stockfish::Move> legalMoves(legalMovesList.size());
            for (int i = 0; i < legalMovesList.size(); i++) {
                legalMoves.insert(*(legalMovesList.begin() + i));
            }

            return legalMoves;
        }

        inline void binaryInsertMoveEval(const MoveEval& moveEval, const unsigned short int startingIndex, const unsigned short int endingIndex) {
            if (endingIndex - startingIndex  <= 1) {
                if (moveEval.eval < moveEvals[startingIndex].eval) {
                    moveEvals.insert(moveEvals.begin() + startingIndex, moveEval);
                }
                else if (moveEval.eval > moveEvals[endingIndex].eval) {
                    moveEvals.insert(moveEvals.begin() + endingIndex + 1, moveEval);
                }
                else {
                    moveEvals.insert(moveEvals.begin() + endingIndex, moveEval);
                }
                return;
            }

            const unsigned short int middleIndex = (startingIndex + endingIndex) / 2;
            if (moveEval.eval > moveEvals[middleIndex].eval) {
                binaryInsertMoveEval(moveEval, middleIndex, endingIndex);
            }
            else {
                binaryInsertMoveEval(moveEval, startingIndex, middleIndex);
            }
        }

        inline void generateMoveEvals() {
            std::unordered_set<Stockfish::Move> legalMoves = getLegalMoves();
            moveEvals = std::vector<MoveEval>();
            for (unsigned short int i = 0; i < 1858; i++) {
                if (legalMoves.contains(Utils::MOVES[i])) {
                    MoveEval moveEval = MoveEval(Utils::MOVES[i], brain.getOutput(i));
                    if (moveEvals.size() == 0) {
                        moveEvals.push_back(moveEval);
                    }
                    else {
                        binaryInsertMoveEval(moveEval, 0, (unsigned short int)moveEvals.size() - 1);
                    }
                }
            }
        }
    };
};