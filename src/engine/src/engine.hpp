// engine.hpp

#pragma once

#include "infos.hpp"

#include "game.hpp"


class Engine
{
    private:

        Game _game;
        const EngineInfos _infos;

    public:

        Engine();

        ~Engine() = default;

        void update_position(std::string fen);

        std::string find_best_move();

        void quit();
};