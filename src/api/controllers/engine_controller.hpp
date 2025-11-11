// engine_controller.hpp

#pragma once

#include "engine/engine.hpp"
#include "uci/uci.hpp"

#include <unordered_map>


class EngineController
{
    private:
        std::unordered_map<uint64_t, UCI> _sessions;
        uint64_t _session_id = 0;
        IEngineIO& _engine_io;

    public:
        EngineController(IEngineIO& engine_io);
        ~EngineController() = default;

        uint64_t create_session();
        UCI &get_session(uint64_t session_id);
};
