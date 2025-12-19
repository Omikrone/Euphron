#pragma once

#include "game.hpp"

#include "engine/evaluation/evaluation.hpp"


int quiescence(Game& game, Color maximizing_player, int alpha, int beta, bool& search_flag);