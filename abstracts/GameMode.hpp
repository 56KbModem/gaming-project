//
// Created by marcd on 21-1-2019.
//

#ifndef TOPFORCE_GAMEMODE_HPP
#define TOPFORCE_GAMEMODE_HPP

#include "../gui/TopforceWindow.hpp"
#include "../Topforce.hpp"
#include "../level/MapGraphics.hpp"
#include "../networking/Client.hpp"

namespace tf {
    class GameMode {
    protected:
        tf::TopforceWindow &window;
        tf::level::MapGraphics level;
        sf::View view;
        tf::network::Client client;
        tf::Character ownPlayer;
        std::vector<tf::Character> enemies;

        bool playerExists(const tf::PlayerPacket & packet);
        void setEnemyParams(tf::PlayerPacket & packet);
    public:
        virtual void run() = 0;
        GameMode(tf::TopforceWindow& window, const std::string& mapName, sf::IpAddress & serverIp);
        virtual ~GameMode() = 0;
    };
}

#endif //TOPFORCE_GAMEMODE_HPP
