#include "quiescence.hpp"


Quiescence::Quiescence(Game& game, MVVLVA& mvv_lva) : _game(game), _mvv_lva(mvv_lva) {}

int Quiescence::quiescence(int q_depth, Color maximizing_player, int alpha, int beta, bool& search_flag) {
    _sel_depth = std::max(_sel_depth, q_depth);
    _nb_nodes_visited++;
    Color current_turn = _game.get_current_turn();
    Color opponent = (current_turn == Color::WHITE) ? Color::BLACK : Color::WHITE;
    int stand_pat;

    GameState state = _game.get_game_state();
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
        stand_pat = Evaluation::evaluate_board_for(_game.get_board(), _game.get_current_turn());
        if (q_depth >= MAX_Q_DEPTH) return stand_pat;
        if (stand_pat >= beta) {
            return beta;
        }
        if (stand_pat > alpha) alpha = stand_pat;

        std::vector<Move> moves = _game.get_capture_and_check_moves();
        _mvv_lva.sort_mvv_lva(moves, _game.get_current_turn());

        for (Move m: moves) {
            if (!search_flag) break;
            Bitboards& board = _game.get_board();
            PieceType capturer = board.get_piece_type(current_turn, m.from);
            PieceType captured = board.get_piece_type(opponent, m.to);

            bool res = _game.try_apply_move(m.from, m.to);
            if (!res) {
                std::cerr << "Quiescence: Illegal move attempted: " << m.to_uci() << std::endl;
                std::cerr << "FEN: " << _game.get_fen() << std::endl;
                std::cerr << "State of bitboards:" << std::endl;
                exit(EXIT_FAILURE);
            }
            int score = -quiescence(q_depth + 1, maximizing_player, -beta, -alpha, search_flag);
            _game.unmake_move();
            if (score >= beta) {
                return beta;
            }
            if (score > alpha) alpha = score;
        }

        return alpha;
    }
}

int Quiescence::get_nb_nodes_visited() const {
    return _nb_nodes_visited;
}

void Quiescence::reset_nb_nodes_visited() {
    _nb_nodes_visited = 0;
}