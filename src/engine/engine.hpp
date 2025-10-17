// engine.hpp

#pragma once

#include "uci/parsing/uci_parser.hpp"
#include "engine/search/search.hpp"

#include "game.hpp"
#include <ctime>


/**
 * @brief Main class representing the Engine "Euphron".
 *
 * Implements the search of the best move and the update of it's internal chessboard.
 */
class Engine
{
    private:

        Game _game;
        Search _search;

    public:

        Engine();

        ~Engine() = default;

        /**
         * @brief Updates the internal game board of the engine.
         *
         * @param fen A string respresenting the FEN notation of the game state.
         * @param bb_move The move to play to be updated.
         */
        void update_position(std::string fen, BBMove bb_move);

        /**
         * @brief Finds the best move to play for the engine in the current position.
         *
         * @return The best move found.
         */
        BBMove find_best_move();
};