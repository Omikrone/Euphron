// uci.cpp

#include "uci.hpp"


const EngineInfos Engine::get_infos() const {
    return _infos;
}


const bool UCI::is_ready() const {
    return true;
}
