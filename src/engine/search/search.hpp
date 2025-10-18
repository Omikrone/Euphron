// search.hpp

#include "engine/evaluation/evaluation.hpp"

#include "game.hpp"
#include <vector>


/**
 * @brief Class responsible for the search of the best moves.
 *
 * Implements the search of the best move with a basic minimax implementation.
 */
class Search
{
    private:

        Game& _game;

        /**
         * @brief Represents a node of the minimax search tree, calculate the score of the current node.
         *
         * @param current_depth The depth of the current node.
         * @param max_depth The maximum depth for the search.
         * @return The score evaluated of the current node.
         */
        int node(int current_depth, int max_depth);

    public:

        Search(Game& game);
        ~Search() = default;

        /**
         * @brief Basic implémentation of the minimax algorithm : searches for a given position the relative best move to play.
         *
         * @param depth The maximum depth for the search.
         * @return A vector of the "best" moves to play.
         */
        std::vector<Move> minimax(int depth);
};