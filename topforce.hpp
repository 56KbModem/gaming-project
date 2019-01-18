//
// Topforce main headers file
//

#ifndef TOPFORCE_HEADERS_HPP
#define TOPFORCE_HEADERS_HPP

// Standard library includes
#include <iostream>
#include <algorithm>
#include <functional>
#include <memory>

#include <string>
#include <sstream>
#include <vector>

// SFML includes
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

// Logger include
#include "Log.hpp"

// Global enum classes
namespace tf {
    enum class GameModes {
        None,
        Team_Deathmatch,
        Search_and_Destroy,
        Free_For_All
    };
}

#endif //TOPFORCE_HEADERS_HPP
