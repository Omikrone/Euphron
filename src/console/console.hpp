// console.hpp

#include "uci/uci.hpp"

#include <iostream>
#include <string>


class Console
{
    private:
        UCI _uci;
        std::vector<std::thread> _uci_threads;
        std::shared_ptr<IEngineIO> _engine_io;

    public:

        Console(std::shared_ptr<IEngineIO> engine_io);
        ~Console() = default;

        void run();
};