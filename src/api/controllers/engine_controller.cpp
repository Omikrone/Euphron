// engine_controller.cpp

#include "engine_controller.hpp"


EngineController::EngineController(IEngineIO& engine_io) : _engine_io(engine_io) {}


uint64_t EngineController::create_session() {
    _sessions.try_emplace(_session_id, _engine_io);
    return _session_id++;
}


UCI &EngineController::get_session(uint64_t session_id) {
    return _sessions.at(session_id);
}