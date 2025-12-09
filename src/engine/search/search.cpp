// search.cpp

#include "search.hpp"

#include <chrono>

int cur_depth = 0;

Search::Search(Game& game) : _game(game) {}

int Search::node(int current_depth, int max_depth, bool& search_flag, Color maximizing_player, int alpha, int beta) {
    if (current_depth > cur_depth) {
        cur_depth = current_depth;
        std::cout << "New max depth achieved : " << cur_depth << std::endl;
    }
    _game.next_turn();
    Color current_turn = _game.get_current_turn();
    Color minimizing_player = (maximizing_player == Color::WHITE) ? Color::BLACK : Color::WHITE;

    if (current_depth == max_depth) {
        GameState state = _game.get_game_state();
        int score;
        if (state == GameState::DRAW_BY_75_MOVE_RULE || state == GameState::STALEMATE ||
            state == GameState::DRAW_BY_INSUFFICIENT_MATERIAL || state == GameState::DRAW_BY_FIFTY_MOVE_RULE ||
            state == GameState::DRAW_BY_THREEFOLD_REPETITION)
            score = 0;
        else if (state == GameState::CHECKMATE && current_turn == maximizing_player)
            score = -1000000;
        else if (state == GameState::CHECKMATE)
            score = 1000000;
        else
            score = Evaluation::evaluate_board_for(_game.get_board(), maximizing_player);
        _game.next_turn();
        return score;
    }

    int score;
    int best_score;

    std::vector<Move> moves = _game.get_legal_moves();

    if (current_turn == minimizing_player) {
        best_score = MAX;  // Extremum to update
    }
    else {
        best_score = MIN;
    }

    for (Move& move : moves) {
        if (!search_flag) break;

        bool res = _game.try_apply_move(move.from, move.to);
        if (!res) {
            move.print();
        }
        if (current_turn == minimizing_player) score = node(current_depth + 1, max_depth, search_flag, maximizing_player, MAX, best_score);
        else score = node(current_depth + 1, max_depth, search_flag, maximizing_player, best_score, MIN);
        _game.unmake_move();
        if (current_turn == minimizing_player && score < best_score)
            best_score = score;  // White tries to minimize black score
        else if (current_turn == maximizing_player && score > best_score)
            best_score = score;  // Black wants to maximize its score
        if (current_turn == minimizing_player && score <= alpha || 
            current_turn == maximizing_player && score >= beta) break;
    }

    return best_score;
}

void Search::minimax(int max_depth, std::vector<Move>& best_moves, bool& search_flag) {
    cur_depth = 0;
    int depth = 1;
    int best_score = -200000;
    int beta = MAX;
    int alpha = MIN;

    Color current_turn = _game.get_current_turn();
    std::vector<Move> moves = _game.get_legal_moves();

    while (depth <= max_depth) {
        if (!search_flag) break;
        best_score = -200000;  // Extremum to update
        std::vector<Move> current_depth_best_moves;

        for (Move& m : moves) {
            if (!search_flag) break;
            _game.try_apply_move(m.from, m.to);
            int score = node(1, depth, search_flag, current_turn, alpha, beta);

            if (score == best_score) {
                current_depth_best_moves.push_back(m);
            } else if (score > best_score) {
                best_score = score;
                current_depth_best_moves.clear();  // TODO : clear only move with inferior score
                current_depth_best_moves.push_back(m);
            }
            _game.unmake_move();
        }
        if (search_flag) best_moves = current_depth_best_moves;
        depth++;
    }
    if (best_moves.size() == 0) {
        for (Move& m : moves) {
            best_moves.push_back(m);
        }
    }
}