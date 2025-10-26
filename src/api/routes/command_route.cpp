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
    CROW_ROUTE(app, "/engine/<int>").methods("POST"_method)
    ([&app, &controller](const crow::request& req, int engine_id){

        UCI& uci = controller.get_session(engine_id);

        // Sends a command to the engine
        std::string out = uci.handle_command(req.body);

        return crow::response(200, out);
    });
}