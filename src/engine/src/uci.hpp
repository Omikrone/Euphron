// uci.hpp

#pragma once

#include "engine.hpp"
#include "infos.hpp"
#include "commands.hpp"
#include "cmd_parser.hpp"
#include "uci_parser.hpp"

#include <iostream>
#include <optional>
#include <cstdint>
#include <vector>
#include <unordered_map>


class UCI
{
    private:

        std::unordered_map<uint64_t, Engine> _engines;
        Engine *_engine;

        void select_engine(uint64_t game_id);
        const std::string get_infos() const;
        const std::string is_ready() const;
        void new_game(uint64_t game_id);
        void position(const std::string pos, UCIMove uci_move);
        const std::string go(const std::optional<uint32_t> w_time, const std::optional<uint32_t> b_time);
        std::string stop();
        void quit(uint64_t game_id);

    public:
        UCI() = default;
        ~UCI() = default;

        std::string handle_command(std::string input);
};