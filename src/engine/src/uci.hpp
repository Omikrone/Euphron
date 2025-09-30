// uci.hpp

#include "engine.hpp"
#include "infos.hpp"

#include <iostream>
#include <optional>


class UCI
{
    private:

        Engine _engine;

        const EngineInfos get_infos() const
        const bool is_ready() const;
        void new_game();
        void position(const std::string pos, const std::optional<vector<Move>> moves);
        const std::optional<> go(const std::optional<uint> w_time, const std::optional<uint> b_time);
        std::string stop();
        void quit();

    public:
        UCI();
        ~UCI();

        void loop();
};