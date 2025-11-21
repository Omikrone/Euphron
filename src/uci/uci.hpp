// uci.hpp

#pragma once

#include "engine/engine.hpp"
#include "uci/uci_commands.hpp"
#include "uci/parsing/cmd_parser.hpp"

#include "uci/commands/new_game.hpp"
#include "uci/commands/position.hpp"
#include "uci/commands/go.hpp"
#include "uci/commands/quit.hpp"
#include "uci/commands/is_ready.hpp"
#include "uci/commands/get_infos.hpp"
#include "uci/commands/stop.hpp"

#include <iostream>
#include <sstream>
#include <optional>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <format>
#include <string>
#include <string_view>
#include <set>


/**
 * @brief Class responsible for the UCI Interface.
 *
 * Handles the received commands and the multiple engine instances.
 */
class UCI
{
    private:
        Engine _engine;
        IEngineIO& _engine_io;
        
        /**
         * @brief Splits an input into the different parts of a command.
         * 
         * @param s The input to split.
         */
        std::vector<std::string> split(const std::string& s);

    public:

        UCI(IEngineIO& engine_io);
        ~UCI() = default;
        UCI(const UCI&) = default;
        UCI(UCI&&) = default;

        /**
         * @brief Handles an UCI command.
         * 
         * @param input The command to handle.
         */
        void handle_command(std::string input);
};