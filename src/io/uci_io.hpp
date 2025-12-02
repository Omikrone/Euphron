#pragma once

#include "engine_io.hpp"

#include <string>


/**
 * @class ConsoleIO
 * @brief Implementation of IEngineIO for console input/output.
 *
 * This class handles input and output operations through the console.
 */
class ConsoleIO: public IEngineIO {

    public:
        virtual ~ConsoleIO() = default;

        virtual void output(const std::string& message) override;
};