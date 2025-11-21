#pragma once

#include "position.hpp"


void position(std::vector<std::string>& args, Engine& engine) {
    std::map<POSITION_OPTIONS, std::variant<std::string, std::vector<Move>>> position_options = parse_position_args(args);

    if (position_options.find(POSITION_OPTIONS::STARTPOS) != position_options.end()) {
        engine.update_position("startpos");
    }
    else if (position_options.find(POSITION_OPTIONS::FEN) != position_options.end()) {
        std::string fen = std::get<std::string>(position_options[POSITION_OPTIONS::FEN]);
        // TODO: Handle FEN with spaces
        engine.update_position(fen);
    }

    if (position_options.find(POSITION_OPTIONS::MOVES) != position_options.end()) {
        for (Move& move : std::get<std::vector<Move>>(position_options[POSITION_OPTIONS::MOVES])) {
            engine.play_move(move);
        }
    }
}


const std::map<POSITION_OPTIONS, std::variant<std::string, std::vector<Move>>> parse_position_args(std::vector<std::string>& args) {
    std::map<POSITION_OPTIONS, std::variant<std::string, std::vector<Move>>> options;

    for (int i=0; i < args.size(); i++)
    {
        if (args[i] == "startpos") {
            options.emplace(POSITION_OPTIONS::STARTPOS, "");
        }
        else if (args[i] == "fen") {
            std::string fen = std::format("{} {} {} {} {} {}", args[i+1], args[i+2], args[i+3], args[i+4], args[i+5], args[i+6]);
            options.emplace(POSITION_OPTIONS::FEN, fen);
        }
        else if (args[i] == "moves") {
            std::vector<Move> moves;
            for (size_t j = i + 1; j < args.size(); j++) {
                moves.push_back(Move::from_uci(args[j]));
            }
            options.emplace(POSITION_OPTIONS::MOVES, moves);
        }
    }
    return options;
}