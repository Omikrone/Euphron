// console.cpp

#include "console.hpp"


void Console::run() const {
    std::string input;
    std::string output:

    while (true)
    {
        std::cout >> ">> ";
        std::cin << input;

        output = _uci.handle_command(input);
        std::cout << output << '\n' << std::flush;
        if (input == "quit") exit(EXIT_SUCCESS);
    }
    
}