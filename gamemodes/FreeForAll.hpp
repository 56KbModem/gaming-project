//
// Created by Nathan Hoekstra on 2019-01-21.
//

#ifndef TOPFORCE_FREEFORALL_HPP
#define TOPFORCE_FREEFORALL_HPP


#include "../abstracts/GameMode.hpp"

#include "../Topforce.hpp"
#include "../gui/TopforceWindow.hpp"
#include "../level/MapGraphics.hpp"
#include "../character/Player.hpp"
#include "../Action.hpp"
#include "../abstracts/GameMode.hpp"
#include "../networking/Client.hpp"

namespace tf{ namespace gamemode{
class FreeForAll : public GameMode {
private:
    std::thread sendThread;
    tf::PlayerPacket packet;
    tf::PlayerPacket serverPacket;
public:
    FreeForAll(tf::TopforceWindow & window, const std::string & mapName, sf::IpAddress & serverIp);
    void run() override;
    void send();
    ~FreeForAll();
};
}}


#endif //TOPFORCE_FREEFORALL_HPP
