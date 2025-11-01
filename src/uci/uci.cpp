// uci.cpp

#include "uci.hpp"


UCI::UCI() : _engine() {}


std::vector<std::string> UCI::split(const std::string& s) {
    std::istringstream iss(s);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) tokens.push_back(token);
    return tokens;
}


std::string UCI::handle_command(std::string input) {

    std::string output;

    std::cout << input << std::endl;
    std::vector args = UCI::split(input);
    std::cout << args.size() << std::endl;

    std::optional<UCICommands> uci_cmd = CommandParser::parse_command(args.at(0));
    if (uci_cmd == std::nullopt) {
        return "Unknown command. Please retry.";
    }

    switch (uci_cmd.value())
    {
        case UCICommands::CMD_UCI:
            output = get_infos();
            break;
        case UCICommands::CMD_IS_READY:
            output = is_ready();
            break;
        case UCICommands::CMD_UCI_NEW_GAME:
            new_game(_engine);
            break;
        case UCICommands::CMD_POSITION:
            position(args, _engine);
            break;
        case UCICommands::CMD_GO:
            output = go(args, _engine);
            break;
        case UCICommands::CMD_QUIT:
            quit();
            break;
        default:
            break;
    }
    return output;
}