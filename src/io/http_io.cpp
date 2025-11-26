#include "http_io.hpp"


HttpEngineIO::HttpEngineIO(crow::websocket::connection *conn) :
    _conn(conn)
{}

void HttpEngineIO::output(const std::string& message) {
    std::cout << "Sending message: " << message << std::endl;
    if (!_conn) {
        std::cerr << "Error: WebSocket connection is null." << std::endl;
        return;
    }
    _conn->send_text(message);
}