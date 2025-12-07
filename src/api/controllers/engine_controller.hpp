// engine_controller.hpp

#pragma once

#include <memory>
#include <unordered_map>

#include "engine/engine.hpp"
#include "io/http_io.hpp"
#include "uci/uci.hpp"

/**
 * @class EngineController
 * @brief Controller class to manage multiple engine sessions.
 *
 * This class handles the creation and retrieval of UCI engine sessions identified by unique session IDs.
 */
class EngineController {
   private:
    std::unordered_map<uint64_t, UCI> _sessions;

   public:
    EngineController();
    ~EngineController() = default;

    /**
     * @brief Creates a new engine session.
     * @param conn The WebSocket connection associated with the session.
     * @param session_id The unique identifier for the session.
     * @return The unique session ID.
     */
    uint64_t create_session(crow::websocket::connection& conn, int session_id);

    /**
     * @brief Retrieves an existing engine session by its ID.
     * @param session_id The unique identifier for the session.
     * @return Reference to the UCI engine session.
     */
    UCI& get_session(uint64_t session_id);

    /**
     * @brief Checks if a session with the given ID exists.
     * @param session_id The unique identifier for the session.
     * @return True if the session exists, false otherwise.
     */
    bool has_session(uint64_t session_id);
};
