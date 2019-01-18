//
// Topforce main headers file
//

#ifndef TOPFORCE_HEADERS_HPP
#define TOPFORCE_HEADERS_HPP

// Standard library includes
#include <iostream>
#include <functional>
#include <cstdint>
#include <memory>

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
namespace tf {
    enum class game_modes {
        None,
        Team_Deathmatch,
        Search_and_Destroy,
        Free_For_All
    };

    struct network_packet {
        sf::IpAddress ip_sender;
        float x;
        float y;
        float rotation;
        uint8_t firing;
        char * nickname[32];
    };
}

#endif //TOPFORCE_HEADERS_HPP
