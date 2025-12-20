#pragma once

#include "game.hpp"

#include "engine/evaluation/evaluation.hpp"


constexpr int MAX_Q_DEPTH = 4;

int quiescence(Game& game, int q_depth, Color maximizing_player, int alpha, int beta, bool& search_flag);