#pragma once

#include "engine/evaluation/piece_values.hpp"

#include <algorithm>
#include <vector>
#include "board/bitboards.hpp"
#include "moves/move.hpp"


/**
 * @brief Class responsible for the MVV-LVA move ordering heuristic.
 *
 * Implements the Most Valuable Victim - Least Valuable Aggressor (MVV-LVA) heuristic to sort moves.
 */
class MVVLVA {
    private:
        Bitboards& _board;

        /**
         * @brief Calculates the MVV-LVA score for a given move.
         *
         * @param move The move to evaluate.
         * @param side The color of the moving piece.
         * @param opponent The color of the opponent's piece.
         * @return The MVV-LVA score of the move.
         */
        int mvv_lva(Move& move, const Color side, const Color opponent);

    public:
        MVVLVA(Bitboards& board);
        ~MVVLVA() = default;

        /**
         * @brief Sorts a vector of moves using the MVV-LVA heuristic.
         *
         * @param moves The vector of moves to sort.
         * @param side The color of the moving pieces.
         */
        void sort_mvv_lva(std::vector<Move>& moves, const Color side);
};