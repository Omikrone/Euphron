#pragma once

#include "engine_io.hpp"
#include "api/controller/engine_controller.hpp"

#include <crow.h>
#include <string>
#include "crow/middlewares/cors.h"


class HttpEngineIO: public IEngineIO {
    private:
        crow::App<crow::CORSHandler>& _app;
        EngineController& _controller;

    public:

        HttpEngineIO(crow::App<crow::CORSHandler>& app, EngineController& controller);
        ~HttpEngineIO() = default;

        void output(const std::string& message) override;
};