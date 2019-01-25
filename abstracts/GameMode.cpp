//
// Created by marcd on 21-1-2019.
//

#include "GameMode.hpp"

namespace tf {
    GameMode::GameMode(tf::TopforceWindow &window, const std::string &mapName):
        window(window),
        level(mapName, window),
        ownPlayer(window, view, sf::IpAddress::getLocalAddress().toInteger())
    {
        view.setSize(1920.f, 1080.f);
    }
    GameMode::~GameMode() {

    }
}