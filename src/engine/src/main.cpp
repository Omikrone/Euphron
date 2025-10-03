#include "uci.hpp"
#include "api/routes/command_route.hpp"


#include "crow.h"
#include "crow/middlewares/cors.h"

using namespace crow;


int main() {

    crow::App<crow::CORSHandler> app;
    std::vector<std::unique_ptr<Game>> games;

    UCI interface;
    register_command_routes(app, interface);

    // Runs the app on port 18080
    app.port(18080).multithreaded().run();
}