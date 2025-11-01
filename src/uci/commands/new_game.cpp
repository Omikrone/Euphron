#include "uci/commands/new_game.hpp"


void new_game(Engine& engine) {
    std::vector<std::string> args;
    args.push_back("position");
    args.push_back("startpos");
    position(args, engine);
}