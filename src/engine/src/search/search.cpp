// search.cpp

#include "search.hpp"


Search::Search(Game& game) : _game(game) {}


int Search::make_move(int current_depth, int max_depth) {


    if (current_depth == max_depth) {        
        
        return Evaluation::evaluate_board_for(_game.get_board(), Color::BLACK);
    }

    int score;
    int best_score;

    _game.next_turn();
    //std::cout << "Current depth : " << current_depth << std::endl;
    //std::cout << "Before legal moves : " << _game.get_fen() << std::endl;

    Color current_turn = _game.get_current_turn();
    std::vector<Move> moves = _game.get_legal_moves(current_turn);

    if (current_turn == Color::WHITE) best_score = 200000; // Extremum to update
    else best_score = -200000;
    //std::cout << "After legal moves : " << _game.get_fen() << std::endl;

    for (Move& move: moves) {
        
        bool res = _game.try_apply_move(move.from, move.to);
        if (!res) {
            move.print();
            std::cout <<"Invalid move : " << std::endl;
        }
        score = make_move(current_depth + 1, max_depth);
        _game.unmake_move();
        if (current_turn == Color::WHITE && score < best_score) best_score = score; // White tries to minimize black score
        else if (current_turn == Color::BLACK && score > best_score) best_score = score; // Black wants to maximize its score
    }

    return best_score;
}


std::vector<Move> Search::minimax(int depth) {
    std::cout << "beginning minimax" << std::endl;
    int best_score = -200000;
    std::vector<Move> best_moves;

    Color current_turn = _game.get_current_turn();
    std::vector<Move> moves = _game.get_legal_moves(current_turn);
    for (Move& m : moves) {
        //std::cout << "first depth : ";
        //m.print();
        //std::cout << "Before move : " << _game.get_fen() << std::endl;
        bool res = _game.try_apply_move(m.from, m.to);
        if (!res) {
            std::cout << "Invalid move : " << std::endl;
        }
        //std::cout << "After move : " << _game.get_fen() << std::endl;
        int score = make_move(0, 3);
        if (score == best_score) {
            best_moves.push_back(m);
        }
        else if (score > best_score) {
            //std::cout << "Move : ";
            m.print();
            //std::cout << " with score : " << score << std::endl;
            best_score = score;
            best_moves.clear(); // TODO : clear only move with inferior scoree
            best_moves.push_back(m);
        }
        _game.unmake_move();
    }
    int current_score = Evaluation::evaluate_board_for(_game.get_board(), Color::BLACK);
    std::cout << "Final score relative to current position : " << best_score - current_score << std::endl;
    std::cout << "End of minimax" << std::endl;
    return best_moves;
}