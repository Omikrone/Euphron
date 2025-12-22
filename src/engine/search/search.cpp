// search.cpp

#include "search.hpp"

#include <chrono>

int cur_depth = 0;
int nodes_visited = 0;   // total visited nodes
int nb_cutoffs = 0;     // nombre de coupures alpha-beta

Search::Search(Game& game) : _game(game) {}

int Search::node(int current_depth, int max_depth, bool& search_flag, int alpha, int beta) {
    nodes_visited++; 
    if (current_depth > cur_depth) {
        cur_depth = current_depth;
        std::cout << "New max depth achieved : " << cur_depth <<  " : " << max_depth << std::endl;
    }
    Color current_turn = _game.get_current_turn();
    if (current_depth == max_depth) return quiescence(_game, 1, current_turn, alpha, beta, search_flag);

    int score;
    int best_score = MIN;
    std::string best_fen;

    std::vector<Move> moves = _game.get_legal_moves();

    for (Move& move : moves) {
        if (!search_flag) break;

        bool res = _game.try_apply_move(move.from, move.to);
        if (!res) {
            move.print();
        }

        score = -node(current_depth + 1, max_depth, search_flag, -beta, -alpha);
        _game.unmake_move();

        if (score > best_score) {
            best_score = score;            
        }
        if (score > alpha) alpha = score;
        if (alpha >= beta) {
            nb_cutoffs++;
            break;
        }
    }

    return best_score;
}

void Search::negamax(int max_depth, std::vector<Move>& best_moves, bool& search_flag) {
    std::cout << "MINIMAX" << std::endl;
    cur_depth = 0;
    nodes_visited = 0;
    nb_cutoffs = 0;
    int depth = 1;
    int best_score, overall_best_score;
    std::vector<Move> moves = _game.get_legal_moves();
    std::vector<Move> current_depth_best_moves;
    Move pv = {-1, -1, MoveType::NORMAL, false};

    while (depth <= max_depth) {
        if (!search_flag) break;
        best_score = MIN;  // Extremum to update
        int alpha = MIN;

        auto it = std::find(moves.begin(), moves.end(), pv);
        if (it != moves.end()) {
            std::swap(moves[0], *it);
        }
        current_depth_best_moves.clear();

        for (Move& m : moves) {
            if (!search_flag) break;
            _game.try_apply_move(m.from, m.to);
            int score = -node(1, depth, search_flag, alpha, MAX);

            if (score == alpha) {
                current_depth_best_moves.push_back(m);
            } else if (score > alpha) {
                alpha = score;
                current_depth_best_moves.clear();
                current_depth_best_moves.push_back(m);
            }
            _game.unmake_move();
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
    std::cout << "Nodes visited: " << nodes_visited << ", cutoffs: " << nb_cutoffs << std::endl;
}