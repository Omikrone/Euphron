#include "go.hpp"


const std::string go(std::vector<std::string>& args, Engine& engine) {
    std::map<GO_OPTIONS, std::string> go_options = parse_go_args(args);
    BBMove best_move = engine.find_best_move(3);
    UCIMove uci_move = UCIParser::bb_to_uci(best_move);
    return "bestmove " + uci_move.move;
}


const std::map<GO_OPTIONS, std::string> parse_go_args(std::vector<std::string>& args) {
    std::map<GO_OPTIONS, std::string> options;

    for (int i=0; i < args.size(); i++)
    {
        if (args[i] == "wtime") {
            options.emplace(GO_OPTIONS::W_TIME, args[i + 1]);
        }
        else if (args[i] == "btime") {
            options.emplace(GO_OPTIONS::B_TIME, args[i + 1]);
        }
        else if (args[i] == "winc") {
            options.emplace(GO_OPTIONS::W_INC, args[i + 1]);
        }
        else if (args[i] == "binc") {
            options.emplace(GO_OPTIONS::B_INC, args[i + 1]);
        }
        else if (args[i] == "movetime") {
            options.emplace(GO_OPTIONS::MOVE_TIME, args[i + 1]);
        }
        else if (args[i] == "infinite") {
            options.emplace(GO_OPTIONS::INFINITE, args[i + 1]);
        }
        else if (args[i] == "depth") {
            options.emplace(GO_OPTIONS::DEPTH, args[i + 1]);
        }
    }
    return options;
}