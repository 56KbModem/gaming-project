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
        tf::Player ownPlayer;
        std::vector<tf::Character> enemies;
        sf::Clock deathClock;
        tf::DamagePacket damage;
        const sf::Vector2f spawnPoints[8] = {sf::Vector2f(3165,1760),
                                             sf::Vector2f(3485,2985),
                                             sf::Vector2f(1845,3150),
                                             sf::Vector2f(1275,2485),
                                             sf::Vector2f(815,1955),
                                             sf::Vector2f(895,480),
                                             sf::Vector2f(1700,370),
                                             sf::Vector2f(2470,2135)
        };

        tf::PlayerPacket packet;
        tf::PlayerPacket serverPacket;
        tf::DamagePacket damagePacket;

        bool playerExists(const tf::PlayerPacket & packet);
        void setEnemyParams(tf::PlayerPacket & packet);

        void sendDamage();

    public:
        virtual void run() = 0;
        GameMode(tf::TopforceWindow& window, const std::string& mapName, sf::IpAddress & serverIp);
        virtual ~GameMode() = 0;
        void handleDeathEvent(const tf::DamagePacket& damage);
    };
}

#endif //TOPFORCE_GAMEMODE_HPP
