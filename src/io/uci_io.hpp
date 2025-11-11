#pragma once

#include "engine_io.hpp"

#include <string>


class UCIIO: public IEngineIO {

    public:
        virtual ~UCIIO() = default;

        virtual void output(const std::string& message) override;
};