#pragma once

#include <string>


class IEngineIO {

    public:
        virtual ~IEngineIO() = default;

        virtual void output(const std::string& message) = 0;
};