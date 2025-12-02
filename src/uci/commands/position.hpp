#pragma once

#include "engine/engine.hpp"

#include <variant>
#include <string>
#include <format>
#include <vector>
#include <map>


/**
 * @enum POSITION_OPTIONS
 * @brief Enumeration of options for the "position" command.
 * 
 * This enum defines the various options that can be specified with the "position" command in UCI.
 */
enum class POSITION_OPTIONS {
    FEN,
    MOVES  
};


/**
 * @brief Handles the "position" command : Updates the internal game board of the engine to be synced with the game.
 *
 * @param args Vector of arguments specified by the user.
 * @param engine The engine.
 */
void position(std::vector<std::string>& args, Engine& engine);


/**
 * @brief Parses the arguments for the "position" command.
 * 
 * @param args Vector of the command arguments.
 * @return A map of the arguments associated to their value.
 */
const std::map<POSITION_OPTIONS, std::variant<std::string, std::vector<Move>>> parse_position_args(std::vector<std::string>& args);