#pragma once

#include <cstdint>
#include <fmt/format.h>
#include <iostream>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "engine/engine.hpp"
#include "uci/commands/get_infos.hpp"
#include "uci/commands/go.hpp"
#include "uci/commands/is_ready.hpp"
#include "uci/commands/new_game.hpp"
#include "uci/commands/position.hpp"
#include "uci/commands/quit.hpp"
#include "uci/commands/stop.hpp"
#include "uci/parsing/cmd_parser.hpp"
#include "uci/uci_commands.hpp"

#define IDLE_TIMEOUT 30 // in minutes

/**
 * @brief Class responsible for the UCI Interface.
 *
 * Handles the received commands and the multiple engine instances.
 */
class UCI {
   private:
    Engine _engine;
    std::shared_ptr<IEngineIO> _engine_io;
    std::chrono::steady_clock::time_point _last_activity;

    /**
     * @brief Splits an input into the different parts of a command.
     *
     * @param s The input to split.
     */
    std::vector<std::string> split(const std::string& s);

    /**
     * @brief Resets the idle timer to the current time.
     *
     */
    void reset_idle_timer();

   public:
    UCI(std::shared_ptr<IEngineIO> engine_io);
    ~UCI() = default;

    UCI(const UCI&) = delete;
    UCI& operator=(const UCI&) = delete;

    UCI(UCI&&) = default;
    UCI& operator=(UCI&&) = default;

    /**
     * @brief Handles an UCI command.
     *
     * @param input The command to handle.
     */
    void handle_command(std::string input);

    /**
     * @brief Checks if the engine is idle (not searching) for a long time.
     *
     * @return true if the engine is idle, false otherwise.
     */
    bool is_idle() const;
};