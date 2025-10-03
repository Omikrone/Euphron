// engine.hpp

#pragma once

#include "infos.hpp"
#include "uci_parser.hpp"
#include "game.hpp"


class Engine
{
    private:

        Game _game;
        const EngineInfos _infos;

    public:

        Engine();

        ~Engine() = default;

        void update_position(std::string fen, BBMove bb_move);

        BBMove find_best_move();

        void quit();
};