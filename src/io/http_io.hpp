#pragma once

#include "engine/engine.hpp"
#include "engine_io.hpp"
#include "api/controllers/engine_controller.hpp"

#include <crow.h>
#include <string>
#include "crow/middlewares/cors.h"
#include <iostream>


class HttpEngineIO: public IEngineIO {
    private:

        crow::websocket::connection& _conn;
        UCI& _uci;

    public:

        HttpEngineIO() = default;
        HttpEngineIO(crow::websocket::connection& conn, UCI& uci);
        ~HttpEngineIO() = default;

        void output(const std::string& message) override;
        void set_coonnection(crow::websocket::connection& conn) {
            _conn = conn;
        }
};