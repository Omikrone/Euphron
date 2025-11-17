// uci.cpp

#include "uci.hpp"


UCI::UCI(IEngineIO &engine_io) : _engine(engine_io), _engine_io(engine_io) {}


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
            get_infos(_engine_io);
            break;
        case UCICommands::CMD_IS_READY:
            is_ready(_engine_io);
            break;
        case UCICommands::CMD_UCI_NEW_GAME:
            new_game(_engine);
            break;
        case UCICommands::CMD_POSITION:
            position(args, _engine);
            break;
        case UCICommands::CMD_GO:
            go(args, _engine);
            break;
        case UCICommands::CMD_QUIT:
            quit();
            break;
        case UCICommands::CMD_STOP:
            stop();
            break;
        default:
            break;
    }
    return output;
}