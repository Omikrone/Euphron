#include "uci/commands/is_ready.hpp"


void is_ready(IEngineIO& engine_io) {
    engine_io.output("readyok");
}