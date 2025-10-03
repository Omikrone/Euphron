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


void UCI::position(const std::string pos, UCIMove uci_move) {
    BBMove move = UCIParser::uci_to_bb(uci_move);
    _engine.update_position(pos, move);
}


const std::string UCI::go(const std::optional<uint32_t> w_time, const std::optional<uint32_t> b_time) {
    BBMove best_move = _engine.find_best_move();
    UCIMove uci_move = UCIParser::bb_to_uci(best_move);
    return "bestmove " + uci_move.move;
}


std::string UCI::handle_command(std::string input) {

    std::string output;

    std::optional<UCICommands> cmd = CommandParser::parse_command(input);
    if (cmd == std::nullopt) {
        std::cout << "Unknown command. Please retry." << std::endl;
        return "error";
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
        case UCICommands::CMD_POSITION:
            position("startpos", {input.substr(input.size() - 4)});
            break;
        case UCICommands::CMD_GO:
            output = go(std::nullopt, std::nullopt);
            break;
        case UCICommands::CMD_QUIT:
            return "quit";
        default:
            break;
    }
    return output;
}