#pragma once

#include <unordered_set>

#include "Brain.h"

namespace Bryan {
    class Bryan {
    public:

        struct MoveEval {
            std::string move;
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

        //inline void setPosition(const std::string& fen) {
        //    position.set(fen);
        //}

        bool save();

        bool load();

        float getEval() {
            return brain.getOutput(1858);
        }

        Brain getBrain() {
            return brain;
        }

        //Position getPosition() {
        //    return position;
        //}

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
        1858 - all possible moves (see Utils::MOVE_LIST)
        = 1859
        */
        Brain brain = Brain(68, 2000, 1859);

        //Position position;

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
            /*
            std::vector<uint16_t> legalMovesList = std::vector<uint16_t>();
            if (board.get_next_to_move() == virgo::WHITE) {
                virgo::get_legal_moves<virgo::WHITE>(board, legalMovesList);
            }
            else {
                virgo::get_legal_moves<virgo::BLACK>(board, legalMovesList);
            }

            std::unordered_set<std::string> legalMoves;
            for (uint16_t& move : legalMovesList) {
                legalMoves.insert(virgo::string::move_to_string(move));
            }

            moveEvals = std::vector<MoveEval>();
            for (unsigned short int i = 0; i < 1858; i++) {
                if (legalMoves.contains(Utils::MOVE_LIST[i])) {
                    MoveEval moveEval = MoveEval(Utils::MOVE_LIST[i], brain.getOutput(i));
                    if (moveEvals.size() == 0) {
                        moveEvals.push_back(moveEval);
                    }
                    binaryInsertMoveEval(moveEval, 0, (unsigned short int)moveEvals.size() - 1);
                }
            }
            */
        }
    };
};