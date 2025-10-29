#pragma once

#include "engine/engine.hpp"

#include <vector>
#include <string>
#include <map>

#define MAX_DEPTH 3


enum class GO_OPTIONS {
    W_TIME,
    B_TIME,
    W_INC,
    B_INC,
    MOVE_TIME,
    DEPTH,
    INFINITE
};


/**
 * @brief Handles the "go" command : Searches for the best move to play in the current position.
 *
 * @param args Vector of arguments specified by the user.
 * @param engine The engine.
 * @return A string representing the output of the command.
 */
const std::string go(std::vector<std::string>& args, Engine& engine);


/**
 * @brief Parses the arguments for the "go" command.
 * 
 * @param args Vector of the command arguments.
 * @return A map of the arguments associated to their value.
 */
const std::map<GO_OPTIONS, std::string> parse_args(std::vector<std::string>& args);