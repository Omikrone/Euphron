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


class UCI
{
    private:

        Engine _engine;

        const std::string get_infos() const;
        const std::string is_ready() const;
        void new_game();
        void position(const std::string pos, UCIMove uci_move);
        const std::string go(const std::optional<uint32_t> w_time, const std::optional<uint32_t> b_time);
        std::string stop();
        void quit();

    public:
        UCI();
        ~UCI() = default;

        std::string handle_command(std::string input);
};