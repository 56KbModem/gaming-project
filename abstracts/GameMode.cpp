//
// Created by marcd on 21-1-2019.
//

#include "GameMode.hpp"

namespace tf {
GameMode::GameMode(tf::TopforceWindow &window, const std::string &mapName, sf::IpAddress & serverIp):
    window(window),
    level(mapName, window),
    client(53000, serverIp, 53000),
    ownPlayer(window, view, level.getHitboxes() ,sf::IpAddress::getLocalAddress().toInteger())
{
    view.setSize(1920.f, 1080.f);
}

GameMode::~GameMode() {

}

bool GameMode::playerExists(const tf::PlayerPacket & packet) {
    for (const auto& enemy : enemies) {
        if (enemy.playerID == packet.PlayerId) {
            return true;
        }
    }
    return false;
}

void GameMode::setEnemyParams(tf::PlayerPacket & packet) {
    for (auto& enemy : enemies) {
        if (enemy.playerID == packet.PlayerId) {
            enemy.setPosition(packet.position);
            enemy.setRotation(packet.rotation);
            return;
        }
    }
}
}