#pragma once

#include "engine/engine.hpp"


/**
 * @brief Handles the "uci" command : Gets the informations of the engine.
 *
 * @return A string representing the informations.
 */
void get_infos(IEngineIO& engine_io);