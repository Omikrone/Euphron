// cmd_parser.hpp

#pragma once

#include "uci/uci_commands.hpp"

#include <cstring>
#include <string>
#include <optional>
#include <sstream>


/**
 * @brief Static class responsible for the parsing of the received commands.
 *
 * Handles the parsing of the command, and the given arguments.
 */
class CommandParser
{
    public:

        /**
         * @brief Parses the received UCI command.
         *
         * @param input The received input.
         * @return A constant corresponding to the UCI command.
         */
        static const std::optional<UCICommands> parse_command(std::string input);

        /**
         * @brief Parses optionnal arguments received with the command.
         *
         * @param input The received input.
         * @return A string representing the arguments.
         */
        static const std::string parse_argument(std::string input);
};