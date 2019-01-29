//
// Topforce main headers file
//

#ifndef TOPFORCE_HEADERS_HPP
#define TOPFORCE_HEADERS_HPP

// Standard library includes
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdint>
#include <memory>
#include <time.h>

#include <thread>
#include <string>
#include <sstream>
#include <vector>

// SFML includes
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
//#include <SFML/Time.hpp>

// TopForce includes
#include "Log.hpp"
#include "SoundManager.hpp"
#include "ImageManager.hpp"

// Global enum classes
namespace tf {
    enum class GameModes {
        None,
        Team_Deathmatch,
        Search_and_Destroy,
        Free_For_All
    };

    struct PlayerPacket {
        std::string header;
        std::string playerName;
        sf::Vector2f position;
        float rotation;
        bool walking;
        bool firing = false;
        sf::Uint32 PlayerId = 0;
        sf::Vector2f firePos;
    };

    struct TimePacket {
        std::string header;
        int minutes;
        int seconds;
    };

    struct DamagePacket{
        std::string header;
        sf::Uint32 hitById;
        sf::Uint32 playerId;
        unsigned int damage;
    };
}
#endif //TOPFORCE_HEADERS_HPP
