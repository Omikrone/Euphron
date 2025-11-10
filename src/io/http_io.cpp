#include "http_io.hpp"

#include <iostream>
#include <string>


HttpEngineIO::HttpEngineIO(crow::App<crow::CORSHandler>& app, EngineController& controller):
    _app(app),
    _controller(controller)
{}


void HttpEngineIO::output(const std::string& message) {
 
    UCI& uci = controller.get_session(engine_id);

    // Sends a command to the engine
    std::string out = uci.handle_command(req.body);

    return crow::response(200, out);
}