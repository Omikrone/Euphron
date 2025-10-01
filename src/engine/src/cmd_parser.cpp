// parser.cpp

#include "cmd_parser.hpp"


struct ParseResult
{
    bool success;
    std::string error_msg;
};


const std::optional<UCICommands> CommandParser::parse_command(std::string input) {
    const char *input_ptr = input.c_str();

    if (strcmp(input_ptr, "uci")==0)         return UCICommands::CMD_UCI;
    if (strcmp(input_ptr, "isready")==0)     return UCICommands::CMD_IS_READY;
    if (strcmp(input_ptr, "position")==0)    return UCICommands::CMD_POSITION;
    if (strcmp(input_ptr, "go")==0)          return UCICommands::CMD_GO;
    if (strcmp(input_ptr, "stop")==0)        return UCICommands::CMD_STOP;
    if (strcmp(input_ptr, "quit")==0)        return UCICommands::CMD_QUIT;

    return std::nullopt;
}