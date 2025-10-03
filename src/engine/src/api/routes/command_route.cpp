// command_route.cpp

#include "command_route.hpp"


void register_command_routes(crow::App<crow::CORSHandler>& app, UCI& uci) {
    
    // Creates a new POST route for creating new games
    CROW_ROUTE(app, "/commands").methods("POST"_method)
    ([&app, &uci](const crow::request& req){

        // Creates a new game
        std::string out = uci.handle_command(req.body);

        return crow::response(200, out);
    });
}