// engine.cpp

#include "engine.hpp"


Engine::Engine() : _game(), _search(_game) {}


void Engine::update_position(std::string fen, BBMove bb_move) {
    bool res = _game.try_apply_move(bb_move.from, bb_move.to);
    _game.next_turn();
}


BBMove Engine::find_best_move() {
    std::vector<Move> best_moves = _search.minimax(2);

    std::srand(std::time(nullptr));
    int random_i = rand() % best_moves.size();
    Move best_move = best_moves.at(random_i);

    bool res = _game.try_apply_move(best_move.from, best_move.to);
    std::cout << _game.get_fen() << std::endl;
    _game.next_turn();
    return {best_move.from, best_move.to};
}