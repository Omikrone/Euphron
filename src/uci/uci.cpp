// uci.cpp

#include "uci.hpp"


std::vector<std::string> UCI::split(const std::string& s) {
    std::istringstream iss(s);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) tokens.push_back(token);
    return tokens;
}


void UCI::select_engine(std::vector<std::string>& args) {
    int game_id = std::atoi(args.at(1).c_str());
    std::cout << "Selected engine with gameID : " << std::to_string(game_id) << std::endl;
    auto it = _engines.find(game_id);
    if (it == _engines.end()) _engine = nullptr;
    _engine = &it->second;
}


const std::string UCI::get_infos() const {
    std::string response = "id name Euphron \
                            id author Omikrone \
                            uciok";
    return response;
}


const std::string UCI::is_ready() const {
    return "readyok";
}


void UCI::new_game(std::vector<std::string>& args) {
    int game_id = std::atoi(args.at(1).c_str());
    _engines.try_emplace(game_id);
}


void UCI::position(std::vector<std::string>& args) {
    int pointer = 0;
    if (args[1] == "startpos") {
        _engine->update_position(args[1]);
        pointer = 2;
    }
    else if (args[1] == "fen") {
        std::string fen;
        fen = std::format("{} {} {} {} {} {}", args[2], args[3], args[4], args[5], args[6], args[7]);
        _engine->update_position(fen);
        pointer = 8;
    }
    if (args.size() > pointer && args[pointer] == "moves") {
        for (size_t i = pointer + 1; i < args.size(); i++)
        {
            BBMove move = UCIParser::uci_to_bb({args[i]});
            _engine->play_move(move);
        }   
    }
}


const std::string UCI::go(std::vector<std::string>& args) {
    BBMove best_move = _engine->find_best_move();
    UCIMove uci_move = UCIParser::bb_to_uci(best_move);
    return "bestmove " + uci_move.move;
}


void UCI::quit() {
    exit(EXIT_SUCCESS);
}


std::string UCI::handle_command(std::string input) {

    std::string output;

    std::vector args = UCI::split(input);

    std::optional<UCICommands> uci_cmd = CommandParser::parse_command(args.at(0));
    if (uci_cmd == std::nullopt) {
        std::cout << "Unknown command. Please retry." << std::endl;
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
        case UCICommands::CMD_SELECT:
            select_engine(args);
            break;
        case UCICommands::CMD_UCI_NEW_GAME:
            new_game(args);
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