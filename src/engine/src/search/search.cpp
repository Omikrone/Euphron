// search.cpp

#include "search.hpp"


Search::Search(Game& game) : _game(game) {}


int Search::make_move(int best_score, int current_depth, int max_depth) {
    int score;

    if (current_depth == max_depth) {        
        score = Evaluation::evaluate_board(_game.get_board(), Color::BLACK);
        _game.unmake_move();
        current_depth--;
        return score;
    }
    current_depth++;
    _game.next_turn();
    std::cout << "Current depth : " << current_depth << std::endl;

    Color current_turn = _game.get_current_turn();
    std::vector<Move> moves = _game.get_legal_moves(current_turn);

    for (int move_i = 0; move_i < moves.size(); move_i++) {
        Move move = moves.at(move_i);
        _game.try_apply_move(move.from, move.to);
        score = make_move(best_score, current_depth, max_depth);
        if (current_turn == Color::BLACK && score > best_score) best_score = score;
        else if (current_turn == Color::WHITE && score < best_score) best_score = score;
    }
    return best_score;
}


std::vector<Move> Search::minimax(int depth) {
    std::cout << "beginning minimax" << std::endl;
    int best_score = -1;
    std::vector<Move> best_moves;

    Color current_turn = _game.get_current_turn();
    std::vector<Move> moves = _game.get_legal_moves(current_turn);
    for (Move& m : moves) {
        _game.try_apply_move(m.from, m.to);
        _game.next_turn();
        int score = make_move(best_score, 0, 2);
        if (score > best_score) {
            best_score = score;
            best_moves.push_back(m);
        }
        _game.unmake_move();
    }
    return best_moves;
}