//
// Created by marcd on 21-1-2019.
//

#ifndef TOPFORCE_GAMEMODE_HPP
#define TOPFORCE_GAMEMODE_HPP

#include "../gui/TopforceWindow.hpp"
#include "../Topforce.hpp"
#include "../level/MapGraphics.hpp"

namespace tf {
    class GameMode {
    protected:
        tf::TopforceWindow &window;
        tf::level::MapGraphics level;
        sf::View view;
        tf::Character ownPlayer;
    public:
        virtual void run() = 0;
        GameMode(tf::TopforceWindow& window, const std::string& mapName);
    };
}

#endif //TOPFORCE_GAMEMODE_HPP
