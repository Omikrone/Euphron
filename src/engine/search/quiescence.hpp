#pragma once

#include "game.hpp"
#include "engine/search/mvv_lva.hpp"

#include "engine/evaluation/evaluation.hpp"


constexpr int MAX_Q_DEPTH = 4;


/**
 * @brief Class responsible for the quiescence search.
 *
 * Implements a quiescence search to extend the search in volatile positions.
 */
class Quiescence {
private:
    Game& _game;
    MVVLVA& _mvv_lva;
    int _nb_nodes_visited = 0;
    int _sel_depth = 0;

public:
    Quiescence(Game& game, MVVLVA& mvv_lva);
    ~Quiescence() = default;

    /**
     * @brief Quiescence search implementation.
     *
     * @param q_depth The current depth of the quiescence search.
     * @param maximizing_player The color of the maximizing player.
     * @param alpha The alpha value for alpha-beta pruning.
     * @param beta The beta value for alpha-beta pruning.
     * @return The evaluated score of the position.
     */
    int quiescence(int q_depth, Color maximizing_player, int alpha, int beta, bool& search_flag);

    /**
     * @brief Gets the number of nodes visited during the quiescence search.
     *
     * @return The number of nodes visited.
     */
    int get_nb_nodes_visited() const;

    /**
     * @brief Resets the number of nodes visited counter.
     *
     */
    void reset_nb_nodes_visited();

    /**
     * @brief Gets the selective depth reached during the quiescence search.
     *
     * @return The selective depth.
     */
    int get_sel_depth() const { return _sel_depth; }

    /**
     * @brief Resets the selective depth counter.
     *
     */
    void reset_sel_depth() { _sel_depth = 0; }
};
