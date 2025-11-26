// engine_controller.cpp

#include "engine_controller.hpp"


EngineController::EngineController() {}


uint64_t EngineController::create_session(crow::websocket::connection& conn, int session_id) {
    std::shared_ptr<IEngineIO> http_io = std::make_shared<HttpEngineIO>(&conn);
    _sessions.try_emplace(session_id, http_io);
    return session_id;
}

UCI& EngineController::get_session(uint64_t session_id) {
    return _sessions.at(session_id);
}

bool EngineController::has_session(uint64_t session_id) {
    return _sessions.find(session_id) != _sessions.end();
}