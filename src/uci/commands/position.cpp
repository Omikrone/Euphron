#pragma once

#include "position.hpp"


void position(std::vector<std::string>& args, Engine& engine) {
    std::cout << args.size() << std::endl;
    int pointer = 0;
    if (args[1] == "startpos") {
        engine.update_position(args[1]);
        pointer = 2;
    }
    else if (args[1] == "fen") {
        std::string fen;
        fen = std::format("{} {} {} {} {} {}", args[2], args[3], args[4], args[5], args[6], args[7]);
        std::cout << fen << std::endl;
        engine.update_position(fen);
        pointer = 8;
    }
    std::cout << "Pointer value : " << args[pointer + 1] << std::endl;
    if (args.size() > pointer && args[pointer] == "moves") {
        for (size_t i = pointer + 1; i < args.size(); i++)
        {
            std::cout << "apply move" << std::endl;
            BBMove move = UCIParser::uci_to_bb({args[i]});
            engine.play_move(move);
        }   
    }
}


const std::map<POSITION_OPTIONS, std::string> parse_position_args(std::vector<std::string>& args) {
    std::map<POSITION_OPTIONS, std::string> options;

    for (int i=0; i < args.size(); i++)
    {
        if (args[i] == "wtime") {
            options.emplace(POSITION_OPTIONS::FEN, args[i + 1]);
        }
        else if (args[i] == "btime") {
            options.emplace(POSITION_OPTIONS::MOVES, args[i + 1]);
        }
    }
    return options;
}