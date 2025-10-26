// uci.cpp

#include "uci.hpp"


void UCI::select_engine(uint64_t game_id) {
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


void UCI::new_game(uint64_t game_id) {
    _engines.try_emplace(game_id);
}


void UCI::position(const std::string pos, UCIMove uci_move) {
    BBMove move = UCIParser::uci_to_bb(uci_move);
    _engine->update_position(pos, move);
}


const std::string UCI::go(const std::optional<uint32_t> w_time, const std::optional<uint32_t> b_time) {
    BBMove best_move = _engine->find_best_move();
    UCIMove uci_move = UCIParser::bb_to_uci(best_move);
    return "bestmove " + uci_move.move;
}

void UCI::quit(uint64_t game_id) {
    _engines.erase(game_id);
}


std::string UCI::handle_command(std::string input) {

    std::string output;

    std::optional<UCICommands> cmd = CommandParser::parse_command(input);
    if (cmd == std::nullopt) {
        std::cout << "Unknown command. Please retry." << std::endl;
        return "error";
    }
    std::string game_id;

    switch (cmd.value())
    {
        case UCICommands::CMD_UCI:
            output = get_infos();
            break;
        case UCICommands::CMD_IS_READY:
            output = is_ready();
            break;
        case UCICommands::CMD_SELECT:
            game_id = CommandParser::parse_argument(input);
            select_engine(std::stoi(game_id));
            break;
        case UCICommands::CMD_UCI_NEW_GAME:
            game_id = CommandParser::parse_argument(input);
            new_game(std::stoi(game_id));
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