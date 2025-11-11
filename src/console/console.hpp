// console.hpp

#include "uci/uci.hpp"

#include <iostream>
#include <string>


class Console
{
    private:
        UCI _uci;
        std::vector<std::thread> _uci_threads;
        IEngineIO& _engine_io;

    public:

        Console(IEngineIO& engine_io);
        ~Console() = default;

        void run();
};