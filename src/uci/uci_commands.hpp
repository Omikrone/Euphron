#pragma once

/**
 * @enum UCICommands
 * @brief Enumeration of UCI (Universal Chess Interface) commands.
 * 
 * This enum defines the various commands that can be sent to a UCI-compliant chess engine.
 */
enum class UCICommands {
    CMD_UCI,
    CMD_IS_READY,
    CMD_UCI_NEW_GAME,
    CMD_POSITION,
    CMD_GO,
    CMD_STOP,
    CMD_QUIT
};