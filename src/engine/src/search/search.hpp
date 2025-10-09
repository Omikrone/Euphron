// search.hpp

#include "game.hpp"
#include "evaluation/evaluation.hpp"

#include <vector>


class Search
{
    private:

        Game& _game;

        int make_move(int best_score, int current_depth, int max_depth);

    public:

        Search(Game& game);
        ~Search() = default;

        std::vector<Move> minimax(int depth);
};