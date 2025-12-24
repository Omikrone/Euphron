#pragma once

#include "engine/evaluation/piece_values.hpp"

#include <vector>
#include "board/bitboards.hpp"
#include "moves/move.hpp"


class MVVLVA {

    public:
        static int mvv_lva(Bitboards& board, Move& move, const Color side);
        static void sort_mvv_lva(std::vector<Move>& moves);
};