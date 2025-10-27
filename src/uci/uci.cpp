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


const std::string UCI::get_infos() const {
    std::string response = "id name Euphron \n\
                            id author Omikrone \n\
                            uciok";
    return response;
}


const std::string UCI::is_ready() const {
    return "readyok";
}


void UCI::new_game() {
    std::string new_game_cmd = "position startpos";
    handle_command(new_game_cmd);
}


void UCI::position(std::vector<std::string>& args) {
    std::cout << args.size() << std::endl;
    int pointer = 0;
    if (args[1] == "startpos") {
        _engine.update_position(args[1]);
        pointer = 2;
    }
    else if (args[1] == "fen") {
        std::string fen;
        fen = std::format("{} {} {} {} {} {}", args[2], args[3], args[4], args[5], args[6], args[7]);
        std::cout << fen << std::endl;
        _engine.update_position(fen);
        pointer = 8;
    }
    std::cout << "Pointer value : " << args[pointer + 1] << std::endl;
    if (args.size() > pointer && args[pointer] == "moves") {
        for (size_t i = pointer + 1; i < args.size(); i++)
        {
            std::cout << "apply move" << std::endl;
            BBMove move = UCIParser::uci_to_bb({args[i]});
            _engine.play_move(move);
        }   
    }
}


const std::string UCI::go(std::vector<std::string>& args) {
    BBMove best_move = _engine.find_best_move();
    UCIMove uci_move = UCIParser::bb_to_uci(best_move);
    return "bestmove " + uci_move.move;
}


void UCI::quit() {
    exit(EXIT_SUCCESS);
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
            new_game();
            break;
        case UCICommands::CMD_POSITION:
            position(args);
            break;
        case UCICommands::CMD_GO:
            output = go(args);
            break;
        case UCICommands::CMD_QUIT:
            quit();
            break;
        default:
            break;
    }
    return output;
}