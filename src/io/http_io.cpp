#include "http_io.hpp"


HttpEngineIO::HttpEngineIO() :
    _conn(*static_cast<crow::websocket::connection*>(nullptr))
{}

HttpEngineIO::HttpEngineIO(crow::websocket::connection& conn) :
    _conn(conn)
{}


void HttpEngineIO::output(const std::string& message) {
    _conn.send_text(message);
}