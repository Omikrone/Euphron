// console.cpp

#include "console.hpp"


void Console::run() {
    std::string input;
    std::string output;

    while (true)
    {
        std::cout << ">> ";
        std::getline(std::cin, input);
        if (input.empty()) continue;

        _uci_threads.emplace_back([this, input]() {
            std::string output = _uci.handle_command(input);
            std::cout << output << '\n' << std::flush;
        });

        if (input == "quit") exit(EXIT_SUCCESS);
    }

}