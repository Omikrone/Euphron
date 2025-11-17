// command_route.cpp

#include "command_route.hpp"


void register_engine_routes(crow::App<crow::CORSHandler>& app, EngineController& controller) {
    
    // Creates a new POST route for creating new games
    CROW_ROUTE(app, "/engine").methods("POST"_method)
    ([&app, &controller](const crow::request& req){

        // Creates a new game
        uint64_t engine_id = controller.create_session();

        crow::json::wvalue response;
        response["session_id"] = engine_id;
        response["status"] = "created";

        crow::response res;
        res.code = 201;
        res.set_header("Content-Type", "application/json");
        res.set_header("Location", "/session/" + std::to_string(engine_id));
        res.write(response.dump());
        return res;
    });

    // Creates a new POST route for sending a command to a session
    CROW_WEBSOCKET_ROUTE(app, "/engine/<int>")
        .onopen([](crow::websocket::connection& /*conn*/) {
            CROW_LOG_INFO << "Client connected!";
        })
        .onmessage([&controller](crow::websocket::connection& conn, const std::string& message, bool /*is_binary*/) {
            try {
                crow::json::rvalue req = crow::json::load(message);
                int session_id = req["session_id"].i();
                uint64_t id = static_cast<uint64_t>(session_id);
                UCI& session = controller.get_session(id);
                std::string response = session.handle_command(req["command"].s());
                conn.send_text(response);
            } catch (const std::exception& e) {
                conn.send_text(std::string("Error: ") + e.what());
            }
        })
        .onclose([](crow::websocket::connection& /*conn*/, const std::string& reason){
            CROW_LOG_INFO << "WebSocket closed for session: " << reason;
        });
}