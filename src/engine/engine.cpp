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


void Engine::start_search(
    std::optional<int> depth, 
    std::optional<int> movetime, 
    std::optional<int> wtime,
    std::optional<int> btime,
    std::optional<int> winc,
    std::optional<int> binc,
    std::optional<bool> infinite
    ) {
    if (_search_flag == true) {
        _engine_io.output("info string A search is already running.");
        return;
    }
    _search_flag = true;
    std::cout << _game.get_fen() << std::endl;

    auto t1 = std::chrono::high_resolution_clock::now();
    std::thread search_thread(&Search::minimax, &_search, depth, std::ref(_best_moves), std::ref(_search_flag));
}


void Engine::stop_search() {
    if (_search_flag == false) {
        _engine_io.output("info string No search to stop.");
        return;
    }
    else {
        _search_flag = false;
        _search_thread.join();
        _engine_io.output("info string Search stopped.");
        int random_i = rand() % _best_moves.size();
        UCIMove best_move = _best_moves.at(random_i);;
        _engine_io.output("bestmove " + best_move.move);
    }
}