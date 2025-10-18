// evaluation.hpp

#include "piece_values.hpp"

#include "game.hpp"


/**
 * @brief Static class responsible for the evaluation of a given position.
 *
 * Implements a basic evaluation only based on the material of the players.
 */
class Evaluation
{

    public:

        /**
         * @brief Evaluate a board (position) for a given player.
         *
         * @param board The board to evaluate.
         * @param player The player to evaluate.
         * @return The relative score of the position for the player in comparison of it's opponent.
         */
        static int evaluate_board_for(Bitboards& board, Color player);

        /**
         * @brief Evaluate the absolute score of a player.
         *
         * @param board The board to evaluate.
         * @param player The player to evaluate.
         * @return The absolute score of the position for the player.
         */
        static int evaluate_player(Bitboards& board, Color player);
};