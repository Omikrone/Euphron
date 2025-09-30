// parser.cpp

#include "parser.hpp"


struct ParseResult
{
    bool success;
    std::string error_msg;
};


const std::optional<UCICommands> Parser::parse_command(std::string input) {
    switch (input)
    {
        case "uci":     return UCICommands::CMD_UCI;
        case "isready":     return UCICommands::CMD_IS_READY;
        case "position":    return UCICommands::CMD_POSITION;
        case "go":          return UCICommands::CMD_GO;
        case "stop":        return UCICommands::CMD_STOP;
        case "quit":        return UCICommands::CMD_QUIT;
        default:            return std::nullopt;
    }
}