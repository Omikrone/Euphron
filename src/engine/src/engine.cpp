// engine.cpp

#include "engine.hpp"


Engine::Engine() : _game(), _infos() {}


void Engine::update_position(std::string fen, BBMove bb_move) {
    bool res = _game.try_apply_move(bb_move.from, bb_move.to);
    _game.next_turn();
}


BBMove Engine::find_best_move() {
    std::vector<Move> moves = _game.get_legal_moves(_game.get_current_turn());
    std::srand(std::time(nullptr));
    int random_i = rand() % moves.size();
    Move random_move = moves.at(random_i);
    bool res = _game.try_apply_move(random_move.from, random_move.to);
    _game.next_turn();
    return {random_move.from, random_move.to};
}