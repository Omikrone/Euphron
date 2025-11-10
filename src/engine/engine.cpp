// engine.cpp

#include "engine.hpp"


Engine::Engine(IEngineIO& engine_io) : _game(), _search(_game), _engine_io(engine_io) {}


void Engine::update_position(std::string fen) {
    _game.load_fen(fen);
    std::cout << "FEN after update : " << _game.get_fen() << std::endl;
}


void Engine::play_move(BBMove& bb_move) {
    bool res = _game.try_apply_move(bb_move.from, bb_move.to);
    if (!res) {
        std::cout << "Invalid move received: " << std::endl;
        std::cout << bb_move.from << " " << bb_move.to;
    }
    _game.next_turn();
}


void Engine::find_best_move(int depth) {
    std::cout << _game.get_fen() << std::endl;
    std::vector<Move> best_moves;

    auto t1 = std::chrono::high_resolution_clock::now();
    std::thread search_thread(&Search::minimax, &_search, depth, std::ref(best_moves));

    if (best_moves.size() == 0) {
        _engine_io.output("info string No legal moves found.");
        return;
    }

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
    UCIMove uci_move = UCIParser::bb_to_uci({best_move.from, best_move.to});
    _engine_io.output("info string Best move found: " + uci_move.move);
    _engine_io.output("bestmove " + uci_move.move);
}


void Engine::stop_search() {
    // Not implemented yet
}