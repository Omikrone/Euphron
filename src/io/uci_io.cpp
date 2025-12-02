#include "uci_io.hpp"

#include <iostream>
#include <string>


void ConsoleIO::output(const std::string& message) {
    std::cout << message << std::endl << std::flush;
}