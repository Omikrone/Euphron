// console.cpp

#include "console.hpp"


Console::Console(std::shared_ptr<IEngineIO> engine_io) : _uci(engine_io), _engine_io(engine_io) {}


void Console::run() {
    std::string input;
    std::string output;

    while (true)
    {
        std::cout << ">> ";
        std::getline(std::cin, input);
        if (input.empty()) continue;

        _uci_threads.emplace_back([this, input]() {
            _uci.handle_command(input);
        });

        if (input == "quit") exit(EXIT_SUCCESS);
    }

}