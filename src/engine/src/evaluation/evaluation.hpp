// evaluation.hpp

#include "game.hpp"
#include "piece_values.hpp"


class Evaluation
{

    public:
        static int evaluate_board_for(Bitboards& board, Color player);
        static int evaluate_player(Bitboards& board, Color player);
};