// uci.hpp

#pragma once

#include "engine/engine.hpp"
#include "uci/uci_commands.hpp"
#include "uci/parsing/cmd_parser.hpp"
#include "uci/parsing/uci_parser.hpp"

#include <iostream>
#include <sstream>
#include <optional>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <format>
#include <string>
#include <string_view>
#include <set>


/**
 * @brief Class responsible for the UCI Interface.
 *
 * Handles the received commands and the multiple engine instances.
 */
class UCI
{
    private:

        std::unordered_map<uint64_t, Engine> _engines;

        Engine *_engine;

        /**
         * @brief Splits an input into the different parts of a command.
         * 
         * @param s The input to split.
         */
        std::vector<std::string> split(const std::string& s);

        /**
         * @brief Selects the corresponding engine to the game.
         *
         * @param game_id The id of the game in which the engine plays.
         */
        void select_engine(std::vector<std::string>& args);


        /**
         * @brief Handles the "uci" command : Gets the informations of the engine.
         *
         * @return A string representing the informations.
         */
        const std::string get_infos() const;


        /**
         * @brief Handles the "isready" command : Checks that the engine is ready to play.
         *
         * @return A string representing the result of the check.
         */
        const std::string is_ready() const;


        /**
         * @brief Handles the "new_game" command : Creates a new instance of the engine for the game.
         *
         * @param game_id The id of the new game.
         */
        void new_game(std::vector<std::string>& args);


        /**
         * @brief Handles the "position" command : Updates the internal game board of the engine to be synced with the game.
         *
         * @param pos A string representing the FEN notation of the current game state.
         * @param uci_move The move to play to be updated.
         */
        void position(std::vector<std::string>& args);


        /**
         * @brief Handles the "go" command : Searches for the best move to play in the current position.
         *
         * @param w_time Maximal time granted to the engine for the search.
         * @param b_time Maximal search depth granted to the engine.
         * @return A string representing the best move found.
         */
        const std::string go(std::vector<std::string>& args);


        /**
         * @brief Handles the "stop" command : Interrupts the search of the engine.
         * 
         * @warning Not implemented yet.
         * @return A string representing the best move found.
         */
        std::string stop();

        
        /**
         * @brief Handles the "quit" command : Terminates the engine's process and clean the data.
         * 
         * @param game_id The id of the game in which the engine must exit.
         */
        void quit();

    public:

        UCI() = default;
        ~UCI() = default;

        /**
         * @brief Handles an UCI command.
         * 
         * @param input The command to handle.
         * @return A string representing the output of the command.
         */
        std::string handle_command(std::string input);
};