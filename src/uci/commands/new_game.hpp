#pragma once

#include "uci/commands/position.hpp"
#include "engine/engine.hpp"


/**
 * @brief Handles the "ucinewgame" command : Resets the engine for a new game.
 *
 * @param engine The engine.
 */
void new_game(Engine& engine);