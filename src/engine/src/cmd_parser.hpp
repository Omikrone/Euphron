// parser.hpp

#pragma once

#include "commands.hpp"

#include <string>
#include <optional>


class CommandParser
{
    public:
        static const std::optional<UCICommands> parse_command(std::string input);
};