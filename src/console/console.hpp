// console.hpp

#include "uci/uci.hpp"

#include <iostream>
#include <string>


class Console
{
    private:
        UCI _uci;

    public:

        Console() = default;
        ~Console() = default;

        void run() const;
};