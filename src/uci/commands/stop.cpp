#include "stop.hpp"

void stop(Engine& engine) {
    std::cout << "Stop command received" << std::endl;
    engine.stop_search();
}