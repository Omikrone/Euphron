// uci.cpp

#include "uci.hpp"

UCI::UCI(std::shared_ptr<IEngineIO> engine_io) : _engine(*engine_io.get()), _engine_io(engine_io) {}

std::vector<std::string> UCI::split(const std::string& s) {
    std::istringstream iss(s);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) tokens.push_back(token);
    return tokens;
}

void UCI::handle_command(std::string input) {
    std::string output;

    std::vector<std::string> args = UCI::split(input);

    std::optional<UCICommands> uci_cmd = CommandParser::parse_command(args.at(0));
    if (uci_cmd == std::nullopt) {
        _engine_io->output("info string Unknown command received.");
        return;
    }
    if (_engine_io == nullptr) {
        std::cerr << "Error: Engine IO is not initialized." << std::endl;
        return;
    }

    switch (uci_cmd.value()) {
        case UCICommands::CMD_UCI:
            get_infos(*_engine_io.get());
            break;
        case UCICommands::CMD_IS_READY:
            is_ready(*_engine_io.get());
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
            stop(_engine);
            break;
        default:
            break;
    }
}