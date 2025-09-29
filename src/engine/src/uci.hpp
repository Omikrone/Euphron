// uci.hpp

#include <iostream>


enum class UCICommands {
    CMD_UCI,
    CMD_IS_READY,
    CMD_UCI_NEW_GAME,
    CMD_POSITION,
    CMD_GO,
    CMD_QUIT
};