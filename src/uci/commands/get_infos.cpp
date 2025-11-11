#include "uci/commands/get_infos.hpp"


void get_infos(IEngineIO& engine_io) {
    std::string response = "id name Euphron \n";
    response += "id author Omikrone \n";
    response += "uciok";
    engine_io.output(response);
}
