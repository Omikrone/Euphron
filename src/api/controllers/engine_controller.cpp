// engine_controller.cpp

#include "engine_controller.hpp"


EngineController::EngineController() {}


uint64_t EngineController::create_session(crow::websocket::connection& conn, int session_id) {
    _sessions.try_emplace(session_id, std::make_shared<HttpEngineIO>(conn));
    return session_id;
}

UCI& EngineController::get_session(uint64_t session_id) {
    return 
}

bool EngineController::has_session(uint64_t session_id) {
    return _sessions.find(session_id) != _sessions.end();
}