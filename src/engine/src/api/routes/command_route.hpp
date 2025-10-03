// game_routes.hpp

#pragma once

#include "uci.hpp"

// Turns off the warning of unreachable code in crow
#pragma warning(push)
#pragma warning(disable : 4702)
#include "crow.h"
#include "crow/middlewares/cors.h"
#pragma warning(pop)


/**
 * @brief Registers the http routes for the API.
 *
 * @param app The Crow app in which to register the routes.
 * @param uci The instance for handling the commands.
 */
void register_command_routes(crow::App<crow::CORSHandler>& app, UCI& uci);