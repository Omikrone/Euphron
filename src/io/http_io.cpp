#include "http_io.hpp"

HttpIO::HttpIO(crow::websocket::connection* conn) : _conn(conn) {}

void HttpIO::output(const std::string& message) {
    std::cout << message << std::endl;
    
    if (!_conn) {
        std::cerr << "Warning: WebSocket connection is null, message not sent." << std::endl;
        return;
    }
    
    try {
        _conn->send_text(message);
    } catch (const std::exception& e) {
        std::cerr << "Error sending WebSocket message: " << e.what() << std::endl;
    }
}