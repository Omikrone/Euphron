#pragma once

#include "engine/engine.hpp"
#include "engine_io.hpp"

#include <crow.h>
#include <string>
#include "crow/middlewares/cors.h"
#include <iostream>


/**
 * @class HttpIO
 * @brief Implementation of IEngineIO for HTTP WebSocket input/output.
 *
 * This class handles input and output operations through a WebSocket connection.
 */
class HttpIO: public IEngineIO {
    private:

        crow::websocket::connection *_conn;

    public:

        HttpIO(crow::websocket::connection *conn);
        ~HttpIO() = default;

        /**
         * @brief Sends a message through the WebSocket connection.
         * @param message The message to be sent.
         */
        void output(const std::string& message) override;
};