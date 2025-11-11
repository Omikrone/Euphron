#pragma once

#include "io/engine_io.hpp"

#include <string>


/**
 * @brief Handles the "isready" command : Checks that the engine is ready to play.
 *
 * @return A string representing the result of the check.
 */
void is_ready(IEngineIO& engine_io);