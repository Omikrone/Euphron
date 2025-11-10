#pragma once

#include "engine_io.hpp"

#include <string>


class IEngineIO: public IEngineIO {

    public:
        virtual ~IEngineIO() = default;

        virtual void output(const std::string& message) override;
};