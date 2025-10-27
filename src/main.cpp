#include "uci/uci.hpp"
#include "api/routes/command_route.hpp"
#include "api/controllers/engine_controller.hpp"
#include "console/console.hpp"

#include "crow.h"
#include "crow/middlewares/cors.h"

using namespace crow;


int main(int argc, char** argv) {
    bool force_http = false;
    for (int i = 1; i < argc; i++)
    {
        std::string arg(argv[i]);
        if (arg == "--http") force_http == true;
    }
    
    if (force_http) {
        crow::App<crow::CORSHandler> app;
        EngineController controller;

        register_engine_routes(app, controller);

        // Runs the app on port 18088
        app.port(18088).multithreaded().run();
    }
    else {
        Console console;
        console.run();
    }

}