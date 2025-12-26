#pragma once

#include "game.hpp"
#include "engine/search/mvv_lva.hpp"

#include "engine/evaluation/evaluation.hpp"


constexpr int MAX_Q_DEPTH = 4;


class Quiescence {
private:
    Game& _game;
    MVVLVA& _mvv_lva;
    int _nb_nodes_visited = 0;
    int _sel_depth = 0;

public:
    Quiescence(Game& game, MVVLVA& mvv_lva);
    ~Quiescence() = default;
    int quiescence(int q_depth, Color maximizing_player, int alpha, int beta, bool& search_flag);
    int get_nb_nodes_visited() const;
    void reset_nb_nodes_visited();
    int get_sel_depth() const { return _sel_depth; }
    void reset_sel_depth() { _sel_depth = 0; }
};
