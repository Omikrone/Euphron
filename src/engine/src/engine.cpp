// engine.cpp

#include "engine.hpp"


Engine::Engine() : _game(), _infos() {}


void Engine::update_position(std::string fen, BBMove bb_move) {
    std::cout << "before update : " + _game.get_fen() << std::endl;
    bool res = _game.try_apply_move(bb_move.from, bb_move.to);
    if (!res) std::cout << "ILLEGAL POSITION" << std::endl;
    _game.next_turn();
    std::cout << "after update : " + _game.get_fen() << std::endl;
}


BBMove Engine::find_best_move() {
    std::cout << "BEFORE move : " + _game.get_fen() << std::endl;
    std::vector<Move> moves = _game.get_legal_moves(_game.get_current_turn());
    std::cout << moves.size() << std::endl;
    std::srand(std::time(nullptr));
    int random_i = rand() % moves.size();
    Move random_move = moves.at(random_i);
    std::cout << random_move.from << " " << random_move.to << std::endl;
    std::cout << "Current turn : " << _game.get_current_turn() << std::endl;
    bool res = _game.try_apply_move(random_move.from, random_move.to);
    if (!res) std::cout << "ILLEGAL MOVE" << std::endl;
    _game.next_turn();
    std::cout << "After move : " + _game.get_fen() << std::endl;
    return {random_move.from, random_move.to};
}