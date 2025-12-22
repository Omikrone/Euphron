#include "quiescence.hpp"

int quiescence_nodes_visited = 0;
int nb_quiescence_cutoffs = 0;

int quiescence(Game& game, int q_depth, Color maximizing_player, int alpha, int beta, bool& search_flag) {
    quiescence_nodes_visited++;
    Color current_turn = game.get_current_turn();
    int stand_pat;

    GameState state = game.get_game_state();
    int score;
    if (state != GameState::CONTINUING) {
        if (state == GameState::DRAW_BY_75_MOVE_RULE || state == GameState::STALEMATE ||
            state == GameState::DRAW_BY_INSUFFICIENT_MATERIAL || state == GameState::DRAW_BY_FIFTY_MOVE_RULE ||
            state == GameState::DRAW_BY_THREEFOLD_REPETITION)
            stand_pat = 0;
        else if (state == GameState::CHECKMATE && current_turn == maximizing_player) 
            stand_pat = -1000000;
        else if (state == GameState::CHECKMATE) 
            stand_pat = 1000000;
        return stand_pat;
    }
    else {
        std::vector<Move> moves = game.get_capture_moves();

        stand_pat = Evaluation::evaluate_board_for(game.get_board(), maximizing_player);
        if (q_depth == MAX_Q_DEPTH) return stand_pat;
        if (stand_pat >= beta) {
            nb_quiescence_cutoffs++;
            return beta;
        }
        if (stand_pat > alpha) alpha = stand_pat;

        //std::cout <<"Number of capturing moves to explore : " << moves.size() << std::endl;
        for (Move m: moves) {
            if (!search_flag) break;
            game.try_apply_move(m.from, m.to);
            int score = -quiescence(game, q_depth + 1, game.get_current_turn(), -beta, -alpha, search_flag);
            game.unmake_move();
            if (score >= beta) {
                nb_quiescence_cutoffs++;
                return beta;
            }
            if (score > alpha) alpha = score;
        }

        return alpha;
    }
}