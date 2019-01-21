//
// Created by Nathan Hoekstra on 2019-01-21.
//

#ifndef TOPFORCE_FREEFORALL_HPP
#define TOPFORCE_FREEFORALL_HPP


#include "../abstracts/GameMode.hpp"

#include "../topforce.hpp"
#include "../gui/TopforceWindow.hpp"
#include "../level/MapGraphics.hpp"
#include "../character/Character.hpp"
#include "../Action.hpp"
#include "../abstracts/GameMode.hpp"
#include "../networking/Client.hpp"

namespace tf{ namespace gamemode{
    class FreeForAll : public GameMode {
    private:
        tf::network::Client client;
        tf::playerPacket packet;
        tf::playerPacket serverPacket;

        tf::Character enemy;

    public:
        FreeForAll(tf::TopforceWindow & window, const std::string & mapName, sf::IpAddress & serverIp);
        void run() override;
    };
}}


#endif //TOPFORCE_FREEFORALL_HPP
