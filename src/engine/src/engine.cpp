// engine.cpp

#include "engine.hpp"


Engine::Engine() : _game(), _infos() {}


std::string Engine::find_best_move() {
    std::vector<Move> moves = _game.getAllMoves(_game.get_current_turn());
    int random_i = rand() % moves.size();
    Move random_move = moves.at(random_i);
    return std::to_string(random_move.from) + std::to_string(random_move.to);
}