#include "uci/uci.hpp"
#include "api/routes/command_route.hpp"
#include "api/controllers/engine_controller.hpp"


#include "crow.h"
#include "crow/middlewares/cors.h"

using namespace crow;


int main() {

    crow::App<crow::CORSHandler> app;
    EngineController controller;

    register_engine_routes(app, controller);

    // Runs the app on port 18088
    app.port(18088).multithreaded().run();
}