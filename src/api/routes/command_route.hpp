// game_routes.hpp

#pragma once

#include <string>

#include "api/controllers/engine_controller.hpp"
#include "crow.h"
#include "crow/middlewares/cors.h"
#include "io/http_io.hpp"
#include "uci/uci.hpp"

/**
 * @brief Registers the http routes for the API.
 *
 * @param app The Crow app in which to register the routes.
 * @param uci The instance for handling the commands.
 */
void register_engine_routes(crow::App<crow::CORSHandler>& app, EngineController& controller);