// engine.cpp

#include "engine.hpp"


Engine::Engine() : _game(), _search(_game) {}


void Engine::update_position(std::string fen) {
    _game.load_fen(fen);
}


void Engine::play_move(BBMove bb_move) {
    bool res = _game.try_apply_move(bb_move.from, bb_move.to);
    if (!res) {
        std::cout << "Invalid move received: " << std::endl;
        std::cout << bb_move.from << " " << bb_move.to;
    }
    _game.next_turn();
}


BBMove Engine::find_best_move() {
    std::cout << _game.get_fen() << std::endl;

    auto t1 = std::chrono::high_resolution_clock::now();
    std::vector<Move> best_moves = _search.minimax(3);
    if (best_moves.size() == 0) return {-1, -1};

    auto t2 = std::chrono::high_resolution_clock::now();
    auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    std::chrono::duration<double, std::milli> ms_double = t2 - t1;

    std::cout << "Move found in " << ms_int.count() << "ms\n";

    std::srand(std::time(nullptr));
    int random_i = rand() % best_moves.size();
    Move best_move = best_moves.at(random_i);

    bool res = _game.try_apply_move(best_move.from, best_move.to);
    std::cout << _game.get_fen() << std::endl;
    _game.next_turn();
    return {best_move.from, best_move.to};
}