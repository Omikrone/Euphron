#pragma once

#include "engine/engine.hpp"
#include "uci/commands/position.hpp"

/**
 * @brief Handles the "ucinewgame" command : Resets the engine for a new game.
 *
 * @param engine The engine.
 */
void new_game(Engine& engine);