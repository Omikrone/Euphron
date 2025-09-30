// parser.hpp

#include "commands.hpp"

#include <string>
#include <optional>


class Parser
{
    public:
        static const std::optional<UCICommands> parse_command(std::string input);
};