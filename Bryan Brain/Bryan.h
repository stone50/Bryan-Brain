#pragma once

#include "Brain.h"
#include "platform_folders.h"

namespace Bryan {

    inline const std::filesystem::path brainLocation = std::filesystem::path(sago::getDataHome()) / "Bryan" / "Bryan's Brain.brain";

    /*
    inputs =
    8 x 8 = 64 - piece placement data
    1 - active color
    1 - castling availability
    1 - en passant target square
    1 - halfmove clock
    1 - fullmove number
    = 69 (nice)

    middles =
    ???
    = 0

    outputs =
    1 - evaluation
    1858 - all possible moves (see Utils::MOVE_LIST)
    = 1859
    */
    Brain brain = Brain(69, 0, 1859);

    bool save() {
        return brain.save(brainLocation);
    }

    bool load() {
        return Brain::load(brainLocation, brain);
    }

};