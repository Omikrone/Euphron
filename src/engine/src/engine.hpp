// engine.hpp

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

        const EngineInfos get_infos() const;

        const bool is_ready() const;

        void new_game();

        void update_position(std::string fen);

        std::string find_best_move();

        void quit();
};