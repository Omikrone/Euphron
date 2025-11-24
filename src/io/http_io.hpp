#pragma once

#include "engine/engine.hpp"
#include "engine_io.hpp"

#include <crow.h>
#include <string>
#include "crow/middlewares/cors.h"
#include <iostream>


class HttpEngineIO: public IEngineIO {
    private:

        crow::websocket::connection& _conn;

    public:

        HttpEngineIO(crow::websocket::connection& conn);
        ~HttpEngineIO() = default;

        void output(const std::string& message) override;
};