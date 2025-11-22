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

int Engine::calculate_time_per_move(
    int wtime,
    int btime,
    int winc,
    int binc
) {
    Color turn = _game.get_current_turn();
    int time;
    int inc;

    if (turn == Color::WHITE) {
        time = wtime;
        inc = winc;
    }
    else {
        time = btime;
        inc = binc;
    }

    int nb_moves = _game.get_nb_moves(turn);
    int moves_to_go = 40 - (nb_moves / 2);
    int time_per_move = time / moves_to_go + inc - 50;
    if (time_per_move < 20) time_per_move = 20;
    return time_per_move;
}


void Engine::update_position(std::string fen) {
    _game.load_fen(fen);
    std::cout << "FEN after update : " << _game.get_fen() << std::endl;
}


void Engine::play_move(Move& move) {
    bool res = _game.try_apply_move(move.from, move.to);
    if (!res) {
        std::cout << "Invalid move received: " << std::endl;
        std::cout << move.from << " " << move.to;
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
    _best_moves.clear();
    if (!movetime.has_value()) {
        if (infinite.has_value() && infinite.value() == true) {
            movetime = std::nullopt;
        }
        else {
            int time_per_move = calculate_time_per_move(
                wtime.value_or(0),
                btime.value_or(0),
                winc.value_or(0),
                binc.value_or(0)
            );
            movetime = time_per_move;
        }
    }

    auto start_time = std::chrono::high_resolution_clock::now();

    std::thread search_thread(
        [this, movetime, depth]() {
            _search.minimax(movetime, depth, _best_moves, _search_flag);
        }
    );
    _search_thread = std::move(search_thread);
    _search_thread.detach();
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
        Move move = _best_moves[random_i];
        _engine_io.output("bestmove " + move.to_uci());
    }
}