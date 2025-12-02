// console.hpp
#pragma once

#include "uci/uci.hpp"

#include <iostream>
#include <string>


/**
 * @class Console
 * @brief Class representing the console interface for the chess engine.
 *
 * This class handles the interaction between the user and the engine through the console.
 */
class Console
{
    private:
        UCI _uci;
        std::vector<std::thread> _uci_threads;
        std::shared_ptr<IEngineIO> _engine_io;

    public:

        Console(std::shared_ptr<IEngineIO> engine_io);
        ~Console() = default;

        /**
         * @brief Runs the console interface, handling user input and engine commands.
         */
        void run();
};