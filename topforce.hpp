//
// Topforce main headers file
//

#ifndef TOPFORCE_HEADERS_HPP
#define TOPFORCE_HEADERS_HPP

// Standard library includes
#include <iostream>
#include <functional>

#include <string>
#include <sstream>
#include <vector>

// SFML includes
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

// Logger includes
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

// Global enum classes
enum class game_mode {
    None,
    Team_Deathmatch,
    Search_and_Destroy,
    Free_For_All
};

#endif //TOPFORCE_HEADERS_HPP
