// command_route.cpp

#include "command_route.hpp"

void register_engine_routes(crow::App<crow::CORSHandler>& app, EngineController& controller) {
    // WebSocket route for engine commands
    CROW_WEBSOCKET_ROUTE(app, "/engine/<int>")
        .onopen([](crow::websocket::connection& /*conn*/) { CROW_LOG_INFO << "Client connected!"; })
        .onmessage([&controller](crow::websocket::connection& conn, const std::string& message, bool /*is_binary*/) {
            try {
                crow::json::rvalue req = crow::json::load(message);
                int session_id = req["session_id"].i();
                uint64_t id = static_cast<uint64_t>(session_id);
                if (!controller.has_session(id)) {
                    controller.create_session(conn, id);
                }
                UCI& session = controller.get_session(id);
                session.handle_command(req["command"].s());
            } catch (const std::exception& e) {
                conn.send_text(std::string("Error: ") + e.what());
            }
        })
        .onclose([](crow::websocket::connection& /*conn*/, const std::string& reason) {
            CROW_LOG_INFO << "WebSocket closed for session: " << reason;
        });
}