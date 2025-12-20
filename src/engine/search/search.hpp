// search.hpp

#include <optional>
#include <vector>
#include <bits/stdc++.h>

#include "engine/search/quiescence.hpp"

#include "game.hpp"

constexpr int MAX = 2000000;
constexpr int MIN = -2000000;

/**
 * @brief Class responsible for the search of the best moves.
 *
 * Implements the search of the best move with a basic negamax implementation.
 */
class Search {
   private:
    Game &_game;

    /**
     * @brief Represents a node of the negamax search tree, calculate the score of the current node.
     *
     * @param current_depth The depth of the current node.
     * @param max_depth The maximum depth for the search.
     * @return The score evaluated of the current node.
     */
    int node(int current_depth, int max_depth, bool &stop_flag, int alpha, int beta);

   public:
    Search(Game &game);
    ~Search() = default;

    /**
     * @brief Basic implémentation of the negamax algorithm : searches for a given position the relative best move to
     * play.
     *
     * @param depth The maximum depth for the search.
     * @return A vector of the "best" moves to play.
     */
    void negamax(int depth, std::vector<Move>& best_moves, bool &stop_flag);
};