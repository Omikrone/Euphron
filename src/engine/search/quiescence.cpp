#include "quiescence.hpp"

int quiescence(Game& game, Color maximizing_player, int alpha, int beta, bool& search_flag) {
    Color current_turn = game.get_current_turn();
    Color minimizing_player = (maximizing_player == Color::WHITE) ? Color::BLACK : Color::WHITE;
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
        if (stand_pat > alpha) alpha = stand_pat;
        if (stand_pat >= beta) return beta;

        //std::cout <<"Number of capturing moves to explore : " << moves.size() << std::endl;
        for (Move m: moves) {
            if (!search_flag) break;
            game.try_apply_move(m.from, m.to);
            int score = -quiescence(game, maximizing_player, -beta, -alpha, search_flag);
            game.unmake_move();
            if (score > alpha) alpha = score;
            if (score >= beta) return beta;
        }

        return alpha;
    }
}