// engine_controller.cpp

#include "engine_controller.hpp"


EngineController::EngineController() {}


uint64_t EngineController::create_session(HttpEngineIO& http_io) {
    _sessions.try_emplace(_session_id, http_io);
    return _session_id++;
}


UCI &EngineController::get_session(uint64_t session_id) {
    return _sessions.at(session_id);
}