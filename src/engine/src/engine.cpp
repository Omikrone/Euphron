// engine.cpp

#include "engine.hpp"


Engine::Engine() : _game(), _infos() {}

void Engine::update_position(std::string fen, BBMove bb_move) {
    _game.try_apply_move(bb_move.from, bb_move.to);
    _game.next_turn();
}


BBMove Engine::find_best_move() {
    std::vector<Move> moves = _game.getAllMoves(_game.get_current_turn());
    int random_i = rand() % moves.size();
    Move random_move = moves.at(random_i);
    return {random_move.from, random_move.to};
}