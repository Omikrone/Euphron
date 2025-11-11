#include "go.hpp"


void go(std::vector<std::string>& args, Engine& engine) {
    std::map<GO_OPTIONS, std::string> go_options = parse_go_args(args);
    std::cout << "GO options parsed: " << go_options.size() << std::endl;
    engine.find_best_move(3);
}


const std::map<GO_OPTIONS, std::string> parse_go_args(std::vector<std::string>& args) {
    std::map<GO_OPTIONS, std::string> options;
    std::cout << "Parsing go args, total args: " << args.size() << std::endl;

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