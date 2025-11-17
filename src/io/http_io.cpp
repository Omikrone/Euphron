#include "http_io.hpp"


HttpEngineIO::HttpEngineIO(crow::websocket::connection& conn, UCI& uci) :
    _conn(conn),
    _uci(uci)
{}


void HttpEngineIO::output(const std::string& message) {

    // Sends a command to the engine
    std::string out = _uci.handle_command(message);

    _conn.send_text(out);
}