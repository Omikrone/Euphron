#include "uci_io.hpp"

#include <iostream>
#include <string>


void IEngineIO::output(const std::string& message) {
    std::cout << message << std::endl;
}