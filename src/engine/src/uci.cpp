// uci.cpp

#include "uci.hpp"


UCI::UCI() : _engine() {}

const std::string UCI::get_infos() const {
    std::string response = "id name Euphron \
                            id author Omikrone \
                            uciok";
    return response;
}


const std::string UCI::is_ready() const {
    return "readyok";
}


void UCI::new_game() {}


void UCI::position(const std::string pos, const std::optional<std::vector<Move>> moves) {}


const std::string UCI::go(const std::optional<uint32_t> w_time, const std::optional<uint32_t> b_time) {
    std::string best_move = _engine.find_best_move();
    return "bestmove " + best_move;
}


void UCI::loop() {
    std::string input;
    std::string output;

    while (true)
    {
        std::cout << ">> ";
        std::cin >> input;

        std::optional<UCICommands> cmd = CommandParser::parse_command(input);
        if (cmd == std::nullopt) {
            std::cout << "Unknown command. Please retry." << std::endl;
            continue;
        }

        switch (cmd.value())
        {
            case UCICommands::CMD_UCI:
                output = get_infos();
                break;
            case UCICommands::CMD_IS_READY:
                output = is_ready();
                break;
            case UCICommands::CMD_UCI_NEW_GAME:
                new_game();
                break;
            case UCICommands::CMD_GO:
                output = go(std::nullopt, std::nullopt);
                break;
            case UCICommands::CMD_QUIT:
                return;
            default:
                break;
        }
        std::cout << output << std::endl;
    }
}