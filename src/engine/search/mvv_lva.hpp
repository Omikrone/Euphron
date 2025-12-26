#pragma once

#include "engine/evaluation/piece_values.hpp"

#include <algorithm>
#include <vector>
#include "board/bitboards.hpp"
#include "moves/move.hpp"


class MVVLVA {
    private:
        Bitboards& _board;
        int mvv_lva(Move& move, const Color side, const Color opponent);

    public:
        MVVLVA(Bitboards& board);
        void sort_mvv_lva(std::vector<Move>& moves, const Color side);
};