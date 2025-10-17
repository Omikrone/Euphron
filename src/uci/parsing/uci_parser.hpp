// parser.hpp

#pragma once

#include "parser.hpp"

#include <string>


struct UCIMove
{
    const std::string move;
};

struct BBMove
{
    int from;
    int to;
};


/**
 * @brief Static class representing the parsing of the client's data.
 *
 * Handles the conversion between UCI and Bitboards format.
 */
class UCIParser {

    public:

        /**
         * @brief Parses an move in UCI format to a move in Bitboards format.
         *
         * @param uci_move The move in UCI format.
         * @return The move in Bitboards format.
         */
        static BBMove uci_to_bb(UCIMove uci_move);


        /**
         * @brief Parses an move in Bitboards format to a move in UCI format.
         *
         * @param bb_move The move in Bitboards format.
         * @return The move in UCI format.
         */
        static UCIMove bb_to_uci(BBMove bb_move);
};
