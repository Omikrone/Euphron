// game_routes.hpp

#pragma once

#include "uci/uci.hpp"
#include "api/controllers/engine_controller.hpp"

// Turns off the warning of unreachable code in crow
#pragma warning(push)
#pragma warning(disable : 4702)
#include "crow.h"
#include "crow/middlewares/cors.h"
#pragma warning(pop)
#include <string>


/**
 * @brief Registers the http routes for the API.
 *
 * @param app The Crow app in which to register the routes.
 * @param uci The instance for handling the commands.
 */
void register_engine_routes(crow::App<crow::CORSHandler>& app, EngineController& controller);