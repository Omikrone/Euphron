// engine.cpp

#include "engine.hpp"


Engine::Engine() : _game(), _search(_game) {}


void Engine::update_position(std::string fen, BBMove bb_move) {
    bool res = _game.try_apply_move(bb_move.from, bb_move.to);
    _game.next_turn();
}


BBMove Engine::find_best_move() {
    std::cout << _game.get_fen() << std::endl;
    std::vector<Move> best_moves = _search.minimax(3);
    std::cout << "Number of moves : " << best_moves.size() << std::endl;

    std::srand(std::time(nullptr));
    int random_i = rand() % best_moves.size();
    Move best_move = best_moves.at(random_i);
    std::cout << "Selected move : ";
    best_move.print();
    std::cout << std::endl;

    bool res = _game.try_apply_move(best_move.from, best_move.to);
    std::cout << _game.get_fen() << std::endl;
    _game.next_turn();
    return {best_move.from, best_move.to};
}