// search.cpp

#include "search.hpp"

#include <chrono>


Search::Search(Game& game) : _game(game) {}


int Search::node(int current_depth, int max_depth, bool &search_flag) {

    _game.next_turn();
    Color current_turn = _game.get_current_turn();

    if (current_depth == max_depth) {        
        EndGame state = _game.get_game_state();
        _game.next_turn();
        if (state == EndGame::STALEMATE) return 0;
        else if (state == EndGame::CHECKMATE && current_turn == Color::BLACK) return -1000000;
        else if (state == EndGame::CHECKMATE) return 1000000;
        else return Evaluation::evaluate_board_for(_game.get_board(), Color::BLACK);
    }

    int score;
    int best_score;

    std::vector<Move> moves = _game.get_legal_moves(current_turn);

    if (current_turn == Color::WHITE) best_score = 200000; // Extremum to update
    else best_score = -200000;

    for (Move& move: moves) {
        if (!search_flag) break;
        
        bool res = _game.try_apply_move(move.from, move.to);
        if (!res) {
            move.print();
            std::cout <<"Invalid move : " << std::endl;
        }
        score = node(current_depth + 1, max_depth, search_flag);
        _game.unmake_move();
        if (current_turn == Color::WHITE && score < best_score) best_score = score; // White tries to minimize black score
        else if (current_turn == Color::BLACK && score > best_score) best_score = score; // Black wants to maximize its score
    }

    return best_score;
}


void Search::minimax(std::optional<int> time_limit, int depth, std::vector<Move> &best_moves, bool &search_flag) {
    std::cout << "beginning minimax" << std::endl;
    int best_score = -200000;
    std::cout << "Value of options :" << std::endl;
    std::cout << "  - time limit : " << (time_limit.has_value() ? std::to_string(time_limit.value()) : "none") << std::endl;
    std::cout << "  - depth : " << depth << std::endl;

    Color current_turn = _game.get_current_turn();
    std::vector<Move> moves = _game.get_legal_moves(current_turn);
    for (Move& m : moves) {
        std::cout << "Flag status : " << search_flag << std::endl;
        if (!search_flag) break;
        bool res = _game.try_apply_move(m.from, m.to);
        if (!res) {
            std::cout << "Invalid move : " << std::endl;
        }
        
        int score = node(0, depth - 1, search_flag);

        if (score == best_score) {
            best_moves.push_back(m);
        }
        else if (score > best_score) {
            best_score = score;
            best_moves.clear(); // TODO : clear only move with inferior score
            best_moves.push_back(m);
        }
        _game.unmake_move();
    }
    int current_score = Evaluation::evaluate_board_for(_game.get_board(), Color::BLACK);
    std::cout << "Final score relative to current position : " << best_score - current_score << std::endl;
    std::cout << "End of minimax" << std::endl;
    if (best_moves.size() == 0) {
        for (Move& m : moves) {
            best_moves.push_back(m);
        }
    }
    std::cout << "Number of best moves found: " << best_moves.size() << std::endl;
}