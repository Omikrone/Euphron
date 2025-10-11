// search.cpp

#include "search.hpp"


Search::Search(Game& game) : _game(game) {}


int Search::make_move(int current_depth, int max_depth) {
    int score;
    int best_score = -200000;

    if (current_depth == max_depth) {        
        
        score = Evaluation::evaluate_board_for(_game.get_board(), Color::BLACK);
        //std::cout << _game.get_fen() << "score : " << score << std::endl;
        return score;
    }

    _game.next_turn();
    current_depth++;
    //std::cout << "Current depth : " << current_depth << std::endl;
    //std::cout << "Before legal moves : " << _game.get_fen() << std::endl;

    Color current_turn = _game.get_current_turn();
    std::vector<Move> moves = _game.get_legal_moves(current_turn);
    //std::cout << "After legal moves : " << _game.get_fen() << std::endl;

    for (int move_i = 0; move_i < moves.size(); move_i++) {
        Move move = moves.at(move_i);
        
        bool res = _game.try_apply_move(move.from, move.to);
        if (!res) {
            move.print();
            std::cout <<"Invalid move : " << std::endl;
        }
        score = make_move(current_depth, max_depth);
        _game.unmake_move();
        if (current_turn == Color::WHITE && score >= best_score) best_score = score;
        else if (current_turn == Color::BLACK && score <= best_score) best_score = score;
    }

    current_depth--;
    return best_score;
}


std::vector<Move> Search::minimax(int depth) {
    std::cout << "beginning minimax" << std::endl;
    int best_score = -200000;
    std::vector<Move> best_moves;

    Color current_turn = _game.get_current_turn();
    std::vector<Move> moves = _game.get_legal_moves(current_turn);
    for (Move& m : moves) {
        std::cout << "first depth : ";
        m.print();
        std::cout << "Before move : " << _game.get_fen() << std::endl;
        bool res = _game.try_apply_move(m.from, m.to);
        if (!res) {
            std::cout << "Invalid move : " << std::endl;
        }
        std::cout << "After move : " << _game.get_fen() << std::endl;
        int score = make_move(0, 2);
        if (score == best_score) {
            best_moves.push_back(m);
        }
        else if (score > best_score) {
            std::cout << "Move : ";
            m.print();
            std::cout << " with score : " << score << std::endl;
            best_score = score;
            best_moves.clear(); // TODO : clear only move with inferior scoree
            best_moves.push_back(m);
        }
        _game.unmake_move();
    }
    std::cout << "End of minimax" << std::endl;
    return best_moves;
}