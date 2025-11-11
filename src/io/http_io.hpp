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

        crow::App<crow::CORSHandler>& _app;
        UCI& _uci;

    public:

        HttpEngineIO(crow::App<crow::CORSHandler>& app, UCI& uci);
        ~HttpEngineIO() = default;

        void output(const std::string& message) override;
};