// engine_controller.hpp

#pragma once

#include "engine/engine.hpp"
#include "uci/uci.hpp"
#include "io/http_io.hpp"

#include <unordered_map>
#include <memory>


class EngineController
{
    private:
        std::unordered_map<uint64_t, UCI> _sessions;

    public:
        EngineController();
        ~EngineController() = default;

        uint64_t create_session(crow::websocket::connection& conn, int session_id);
        UCI &get_session(uint64_t session_id);
        bool has_session(uint64_t session_id);
};
