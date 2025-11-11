#include "http_io.hpp"


HttpEngineIO::HttpEngineIO(crow::App<crow::CORSHandler>& app, UCI& uci) :
    _app(app),
    _uci(uci)
{}


void HttpEngineIO::output(const std::string& message) {

    // Sends a command to the engine
    std::string out = _uci.handle_command(message);

    return crow::response(200, out);
}