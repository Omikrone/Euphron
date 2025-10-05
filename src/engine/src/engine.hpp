// engine.hpp

#pragma once

#include "infos.hpp"
#include "uci_parser.hpp"
#include "game.hpp"

#include <ctime>


class Engine
{
    private:

        Game _game;
        const EngineInfos _infos;

    public:

        Engine();

        ~Engine() = default;

        void new_game();

        void update_position(std::string fen, BBMove bb_move);

        BBMove find_best_move();

        void quit();
};