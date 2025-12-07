#pragma once

#include <string>

/**
 * @class IEngineIO
 * @brief Interface for engine input/output operations.
 *
 * This interface defines the methods for input and output operations for a chess engine.
 */
class IEngineIO {
   public:
    virtual ~IEngineIO() = default;

    /**
     * @brief Outputs a message.
     * @param message The message to be outputted.
     */
    virtual void output(const std::string& message) = 0;
};