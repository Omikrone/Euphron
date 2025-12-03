// cmd_parser.cpp

#include "cmd_parser.hpp"

#include <iostream>

struct ParseResult {
    bool success;
    std::string error_msg;
};

const std::optional<UCICommands> CommandParser::parse_command(std::string command) {

    const char *input_ptr = command.c_str();

    if (strcmp(input_ptr, "uci") == 0) return UCICommands::CMD_UCI;
    if (strcmp(input_ptr, "isready") == 0) return UCICommands::CMD_IS_READY;
    if (strcmp(input_ptr, "ucinewgame") == 0) return UCICommands::CMD_UCI_NEW_GAME;
    if (strcmp(input_ptr, "position") == 0) return UCICommands::CMD_POSITION;
    if (strcmp(input_ptr, "go") == 0) return UCICommands::CMD_GO;
    if (strcmp(input_ptr, "stop") == 0) return UCICommands::CMD_STOP;
    if (strcmp(input_ptr, "quit") == 0) return UCICommands::CMD_QUIT;

    return std::nullopt;
}

const std::string CommandParser::parse_argument(std::string input) {
    std::istringstream iss(input);
    std::string argument;
    iss >> argument;
    iss >> argument;
    return argument;
}