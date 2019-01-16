//
// Topforce main headers file
//

#ifndef TOPFORCE_HEADERS_HPP
#define TOPFORCE_HEADERS_HPP

// Standard library includes
#include <iostream>
#include <functional>
#include <cstdint>

#include <string>
#include <sstream>
#include <vector>

// SFML includes
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

// Logger include
#include "log.hpp"

// Global enum classes
enum class game_mode {
    None,
    Team_Deathmatch,
    Search_and_Destroy,
    Free_For_All
};

#endif //TOPFORCE_HEADERS_HPP
