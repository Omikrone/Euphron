#pragma once

#include <string>
#include <iostream>

#include "engine_io.hpp"

/**
 * @class ConsoleIO
 * @brief Implementation of IEngineIO for console input/output.
 *
 * This class handles input and output operations through the console.
 */
class ConsoleIO : public IEngineIO {
   public:
    virtual ~ConsoleIO() = default;

    /**
     * @brief Outputs a message to the console.
     *
     * @param message The message to output.
     */
    virtual void output(const std::string& message) override;
};