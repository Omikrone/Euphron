// console.hpp

#include "uci/uci.hpp"

#include <iostream>
#include <string>


class Console
{
    private:
        UCI _uci;
        std::vector<std::thread> _uci_threads;

    public:

        Console() = default;
        ~Console() = default;

        void run();
};