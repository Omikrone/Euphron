#include "search.hpp"

#include <chrono>


Search::Search(Game& game) : _game(game), _mvv_lva(game.get_board()), _quiescence(game, _mvv_lva) {}

int Search::node(int current_depth, Color maximizing_player, int max_depth, bool& search_flag, int alpha, int beta) {
    _nb_nodes_visited++;
    if (current_depth >= max_depth) return _quiescence.quiescence(1, maximizing_player, alpha, beta, search_flag);
    int score;
    int best_score = MIN;
    std::string best_fen;

    std::vector<Move> moves = _game.get_legal_moves();
    _mvv_lva.sort_mvv_lva(moves, _game.get_current_turn());

    for (Move& move : moves) {
        if (!search_flag) break;

        bool res = _game.try_apply_move(move);
        if (!res) {
            std::cerr << "Search: Illegal move attempted: " << move.to_uci() << std::endl;
            std::cerr << "FEN: " << _game.get_fen() << std::endl;
            exit(EXIT_FAILURE);
        }

        score = -node(current_depth + 1, maximizing_player, max_depth, search_flag, -beta, -alpha);
        _game.unmake_move();

        if (score > best_score) {
            best_score = score;            
        }
        if (score > alpha) alpha = score;
        if (alpha >= beta) {
            break;
        }
    }

    return best_score;
}

void Search::negamax(int max_depth, std::vector<Move>& best_moves, bool& search_flag) {
    _nb_nodes_visited = 0;
    _quiescence.reset_nb_nodes_visited();
    _quiescence.reset_sel_depth();
    std::cout << "MINIMAX with depth " << max_depth << std::endl;
    int depth = 1;
    int overall_best_score;
    std::vector<Move> moves = _game.get_legal_moves();
    std::vector<Move> current_depth_best_moves;
    Move pv = {-1, -1, MoveType::NORMAL, false};
    Color maximizing_player = _game.get_current_turn();

    while (depth <= max_depth) {
        if (!search_flag) break;
        int alpha = MIN;

        _mvv_lva.sort_mvv_lva(moves, _game.get_current_turn());
        auto it = std::find(moves.begin(), moves.end(), pv);
        if (it != moves.end()) {
            std::swap(moves[0], *it);
        }
        current_depth_best_moves.clear();

        for (Move& m : moves) {
            if (!search_flag) break;
            bool res = _game.try_apply_move(m);
            if (!res) {
                std::cerr << "Search: Illegal move attempted: " << m.to_uci() << std::endl;
                std::cerr << "FEN: " << _game.get_fen() << std::endl;
                continue;
            }
            int score = -node(1, maximizing_player, depth, search_flag, alpha, MAX);
            _game.unmake_move();

            if (score == alpha) {
                current_depth_best_moves.push_back(m);
            } else if (score > alpha) {
                alpha = score;
                current_depth_best_moves.clear();
                current_depth_best_moves.push_back(m);
            }
        }
        if (search_flag && !current_depth_best_moves.empty()) {
            pv = current_depth_best_moves.at(0);
            overall_best_score = alpha;
            best_moves = current_depth_best_moves;
            std::cout << "best score for depth : " << depth << " with score: " << overall_best_score << std::endl;
        }
        depth++;
    }
    std::cout << "Best moves size : " << best_moves.size() << std::endl;
    if (best_moves.size() == 0) {
        for (Move& m : moves) {
            best_moves.push_back(m);
        }
    }
    std::cout << "Seldepth reached : " << _quiescence.get_sel_depth() << std::endl;
    std::cout << "Nodes visited in minimax : " << _nb_nodes_visited << std::endl;
    std::cout << "Nodes visited in quiescence : " << _quiescence.get_nb_nodes_visited() << std::endl;
    int total_nodes = _nb_nodes_visited + _quiescence.get_nb_nodes_visited();
    std::cout << "Total nodes visited : " << total_nodes << std::endl;
}