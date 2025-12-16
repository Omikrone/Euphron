// search.cpp

#include "search.hpp"

#include <chrono>

int cur_depth = 0;

Search::Search(Game& game) : _game(game) {}

int Search::node(int current_depth, int max_depth, bool& search_flag, Color maximizing_player, int alpha, int beta) {
    if (current_depth > cur_depth) {
        cur_depth = current_depth;
        std::cout << "New max depth achieved : " << cur_depth <<  " : " << max_depth << std::endl;
    }
    //if (current_depth == 1) std::cout << "Current turn : " << _game.get_current_turn() << std::endl;
    if (current_depth == max_depth) return quiescence(_game, maximizing_player, alpha, beta, search_flag);

    Color current_turn = _game.get_current_turn();
    Color minimizing_player = (maximizing_player == Color::WHITE) ? Color::BLACK : Color::WHITE;
    int score;
    int best_score;
    std::string best_fen;
    Move best_move;

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

        score = node(current_depth + 1, max_depth, search_flag, maximizing_player, alpha, beta);
        // if (current_depth == 2) std::cout << "SCORE : " << score << " POSITION : " << _game.get_fen() << std::endl;
        _game.unmake_move();

        if (current_turn == minimizing_player && score < best_score) {
            // if (current_depth == 2) std::cout << "best score updated from " << best_score << " to " << score << std::endl;
            best_score = score; 
            best_move = move;
            best_fen = _game.get_fen();
        }
        else if (current_turn == maximizing_player && score > best_score) {
            // if (current_depth == 2) std::cout << "best score updated from " << best_score << " to " << score << std::endl;
            best_score = score;
            best_move = move;
            best_fen = _game.get_fen();
            
        }
        if (current_turn == minimizing_player && score < beta) beta = score;
        if (current_turn == maximizing_player && score > alpha) alpha = score;
        if (alpha > beta) break;
    }
    // if (current_depth == 2) {
    //     if (current_turn == minimizing_player) std::cout << "MOVE : " << best_move.to_uci() << " SELECTED FOR MINIMIZING -> Best score : " << best_score << " found with position : " << _game.get_fen() << std::endl;
    //     else if (current_turn == maximizing_player) std::cout << "MOVE : " << best_move.to_uci() << " SELECTED FOR MAXIMIZING -> Best score : " << best_score<< " found with position : " << _game.get_fen() << std::endl;
    // }

    return best_score;
}

void Search::minimax(int max_depth, std::vector<Move>& best_moves, bool& search_flag) {
    std::cout << "MINIMAX" << std::endl;
    cur_depth = 0;
    int depth = 1;
    int best_score = -200000;
    int alpha, beta;
    Color current_turn = _game.get_current_turn();
    std::vector<Move> moves = _game.get_legal_moves();
    std::vector<Move> current_depth_best_moves;

    while (depth <= max_depth) {
        //std::cout << "DEPTH : " << depth << std::endl;
        if (!search_flag) break;
        best_score = -200000;  // Extremum to update
        alpha = MIN;
        beta = MAX;
        current_depth_best_moves.clear();

        for (Move& m : moves) {
            if (!search_flag) break;
            _game.try_apply_move(m.from, m.to);
            int score = node(1, depth, search_flag, current_turn, MIN, beta);

            if (score == best_score) {
                //std::cout << "EQUIVALENT Best score : " << score << " found with position : " << _game.get_fen() << std::endl;
                current_depth_best_moves.clear(); 
                current_depth_best_moves.push_back(m);
            } else if (score > best_score) {
                best_score = score;
                //std::cout << "FINAL Best score : " << score << " found with position : " << _game.get_fen() << std::endl;
                current_depth_best_moves.clear();
                current_depth_best_moves.push_back(m);
            }
            if (score > alpha) {
                alpha = score;
                //std::cout << "Updating ALPHA : " << alpha << std::endl;
            }
            _game.unmake_move();
        }
        //std::cout << "DEPTH FINISHED : ";
        //for (Move& m: current_depth_best_moves) m.print();
        if (search_flag) best_moves = current_depth_best_moves;
        depth++;
    }
    std::cout << "Best moves size : " << best_moves.size() << std::endl;
    if (best_moves.size() == 0) {
        for (Move& m : moves) {
            best_moves.push_back(m);
        }
    }
    std::cout << "final best score found : " << best_score << std::endl;
}