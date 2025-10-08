// evaluation.hpp

#include "game.hpp"
#include "piece_values.hpp"


class Evaluation
{

    public:
        static int evaluate_board(Bitboards& board, Color player);
};