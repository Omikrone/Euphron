#include "engine_controller.hpp"

EngineController::EngineController() {}

uint64_t EngineController::create_session(crow::websocket::connection& conn, int session_id) {
    std::lock_guard<std::mutex> lock(_sessions_mutex);
    std::shared_ptr<IEngineIO> http_io = std::make_shared<HttpIO>(&conn);
    _sessions.try_emplace(session_id, http_io);
    return session_id;
}

UCI& EngineController::get_session(uint64_t session_id) { 
    std::lock_guard<std::mutex> lock(_sessions_mutex);
    return _sessions.at(session_id); 
}

bool EngineController::has_session(uint64_t session_id) { 
    std::lock_guard<std::mutex> lock(_sessions_mutex);
    return _sessions.find(session_id) != _sessions.end(); 
}

void EngineController::free_idle_sessions() {
    std::lock_guard<std::mutex> lock(_sessions_mutex);
    std::vector<uint64_t> sessions_to_remove;
    for (const auto& [session_id, uci] : _sessions) {
        if (uci.is_idle()) {
            _sessions.erase(session_id);
        }
    }
}