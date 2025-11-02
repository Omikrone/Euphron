#include "uci/commands/get_infos.hpp"


const std::string get_infos() {
    std::string response = "id name Euphron \n";
    response += "id author Omikrone \n";
    response += "uciok";
    return response;
}
