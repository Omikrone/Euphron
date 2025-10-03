// parser.hpp

#pragma once

#include "commands.hpp"

#include <cstring>
#include <string>
#include <optional>
#include <sstream>

class CommandParser
{
    public:
        static const std::optional<UCICommands> parse_command(std::string input);
};