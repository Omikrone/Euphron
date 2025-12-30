#pragma once

#include <chrono>
#include <ctime>
#include <optional>
#include <thread>

#include "engine/search/search.hpp"
#include "game.hpp"
#include "io/uci_io.hpp"

#define MAX_DEPTH 10

/**
 * @brief Main class representing the Engine "Euphron".
 *
 * Implements the search of the best move and the update of it's internal chessboard.
 */
class Engine {
   private:
    Game _game;
    Search _search;
    std::thread _search_thread;
    std::thread _timer_thread;
    IEngineIO& _engine_io;
    bool _search_flag;
    std::vector<Move> _best_moves;

   public:
    Engine(IEngineIO& engine_io);

    ~Engine() = default;

    int calculate_time_per_move(int wtime, int btime, int winc, int binc);

    /**
     * @brief Sets a timer thread to stop the search after a given time per move.
     *
     * @param time_per_move The time allocated for the move in milliseconds.
     */
    void set_timer_thread(int time_per_move);

    /**
     * @brief Updates the internal game board of the engine with a position.
     *
     * @param fen A string respresenting the FEN notation of the game state.
     */
    void update_position(std::string fen);

    /**
     * @brief Updates the internal game board of the engine by playing a move.
     *
     * @param move The move to play.
     */
    void play_move(Move& move);

    /**
     * @brief Finds the best move to play for the engine in the current position.
     *
     * @return The best move found.
     */
    void start_search(std::optional<int> depth, std::optional<int> movetime, std::optional<int> wtime,
                      std::optional<int> btime, std::optional<int> winc, std::optional<int> binc,
                      std::optional<bool> infinite);

    /**
     * @brief Stops the current search.
     *
     */
    void stop_search();
};