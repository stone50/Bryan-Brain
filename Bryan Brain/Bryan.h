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

        std::string name = "Bryan";
        
        inline void analyze() {
            setInputs();

            brain.think();

            generateMoveEvals();
        }

        inline void resetBrainState() {
            brain.resetState();
        }

        inline void setPosition(const std::string& fen) {
            Stockfish::StateInfo stateInfo{};
            position.set(fen, false, &stateInfo, position.this_thread());
        }

        bool save();

        bool load();

        float getEval() {
            return brain.getOutput(1858);
        }

        Brain getBrain() {
            return brain;
        }

        const Stockfish::Position& getPosition() {
            return position;
        }

        inline std::vector<MoveEval> getMoveEvals() {
            return moveEvals;
        }

    private:

        const std::filesystem::path projectDataLocation = Utils::DATA_PATH / "Bryan";
        
        /*
        inputs =
        8 x 8 = 64 - piece placement data
        1 - active color
        1 - castling availability
        1 - en passant target square
        1 - halfmove clock
        = 68

        middles =
        ???
        = ?

        outputs =
        1 - evaluation
        1884 - all possible moves (see Utils::MOVE_LIST)
        = 1885
        */
        Brain brain = Brain(68, 25, 1885);

        Stockfish::Position position;

        std::vector<MoveEval> moveEvals;

        inline void setInputs() {
            // piece placement data
            //for (unsigned char i = 0; i < 64; i++) {
            //    brain.setInput(i,);
            //}

            // active color
            //brain.setInput(64,);
            
            // castling availability
            //brain.setInput(65,);

            // en passant target square
            //brain.setInput(66,);

            // halfmove clock
            //brain.setInput(67,);
        }

        std::unordered_set<Stockfish::Move> getLegalMoves() {
            Stockfish::ExtMove* beginMoves = new Stockfish::ExtMove[642];
            Stockfish::ExtMove* endMoves = Stockfish::generate<Stockfish::LEGAL>(position, beginMoves);

            std::unordered_set<Stockfish::Move> legalMoves;
            Stockfish::ExtMove* currentMove = beginMoves;
            while (currentMove != endMoves) {
                legalMoves.insert(*currentMove);
                currentMove++;
            }

            delete[] beginMoves;

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
                    binaryInsertMoveEval(moveEval, 0, (unsigned short int)moveEvals.size() - 1);
                }
            }
        }
    };
};