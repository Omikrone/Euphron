// engine.cpp

#include "engine.hpp"

Engine::Engine(IEngineIO& engine_io) : _game(), _search(_game), _engine_io(engine_io) {}

void Engine::set_timer_thread(int time_per_move) {
    _timer_thread = std::thread([this, time_per_move]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(time_per_move));
        if (_search_flag) {
            stop_search();
        }
    });
    _timer_thread.detach();
}

int Engine::calculate_time_per_move(int wtime, int btime, int winc, int binc) {
    int time;
    int inc;

    if (_game.get_current_turn() == Color::WHITE) {
        time = wtime;
        inc = winc;
    } else {
        time = btime;
        inc = binc;
    }

    int nb_moves = _game.get_fullmove_number();
    int moves_to_go = 40 - (nb_moves / 2);
    int time_per_move = time / moves_to_go + inc - 50;
    if (time_per_move < 20) time_per_move = 20;
    return time_per_move;
}

void Engine::update_position(std::string fen) {
    _game.load_fen(fen);
}

void Engine::play_move(Move& move) {
    bool res = _game.try_apply_move(move.from, move.to);
    if (!res) {
        std::cerr << "Engine: Illegal move attempted: " << move.to_uci() << std::endl;
        std::cerr << "FEN: " << _game.get_fen() << std::endl;
        std::cerr << "State of bitboards:" << std::endl;
        Bitboards& board = _game.get_board();
        _engine_io.output("info string Invalid move received.");
    }
}

void Engine::start_search(std::optional<int> depth, std::optional<int> movetime, std::optional<int> wtime,
                          std::optional<int> btime, std::optional<int> winc, std::optional<int> binc,
                          std::optional<bool> infinite) {
    std::cout << "FEN before search: " << _game.get_fen() << std::endl;
    _engine_io.output("info string Starting search...");
    if (_search_flag == true) {
        _engine_io.output("info string A search is already running.");
        return;
    }
    _search_flag = true;
    _best_moves.clear();
    if (!movetime.has_value()) {
        if (infinite.has_value() && infinite.value() == true && !depth.has_value()) {
            movetime = std::nullopt;
            depth = MAX_DEPTH;
        } else if (wtime.has_value() && btime.has_value()) {
            int time_per_move =
                calculate_time_per_move(wtime.value_or(0), btime.value_or(0), winc.value_or(0), binc.value_or(0));
            movetime = time_per_move;
        }
    }

    _search_thread = std::thread(
        [this, depth]() { _search.negamax(depth.value_or(MAX_DEPTH), _best_moves, _search_flag); });

    if (movetime.has_value() && !infinite.has_value()) {
        set_timer_thread(movetime.value());
    }

    _engine_io.output("info string Search started.");
}

void Engine::stop_search() {
    if (_search_flag == false) {
        _engine_io.output("info string No search to stop.");
        return;
    } else {
        _search_flag = false;
        if (_search_thread.joinable()) {
            _search_thread.join();
        }
        _engine_io.output("info string Search stopped.");
        int random_i = rand() % _best_moves.size();
        Move move = _best_moves[random_i];
        _engine_io.output("bestmove " + move.to_uci());
    }
}