// engine.cpp

#include "engine.hpp"


Engine::Engine() : _game(), _infos() {}


const EngineInfos Engine::get_infos() const {
    return _infos;
}


const bool Engine::is_ready() const {
    return true;
}


void Engine::new_game() {
}


