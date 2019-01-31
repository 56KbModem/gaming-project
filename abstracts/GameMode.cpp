//
// Created by marcd on 21-1-2019.
//

#include "GameMode.hpp"

namespace tf {
GameMode::GameMode(tf::TopforceWindow &window, const std::string &mapName, sf::IpAddress & serverIp):
    window(window),
    level(mapName, window),
    client(serverIp),
    ownPlayer(window, sf::IpAddress::getLocalAddress().toInteger(), view, level.getHitboxes(), enemies, packet)
{
    view.setSize(1920.f, 1080.f);
    ownPlayer.setScore(sf::IpAddress::getLocalAddress().toString());
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
            enemy.firePosition = packet.firePos;
            return;
        }
    }
}
void GameMode::sendDamage() {
    sf::Uint32 enemyID = ownPlayer.getEnemyID();
    if(enemyID > 0){
        damagePacket.playerId = enemyID;
        client.send(damagePacket);
    }
}

void GameMode::handleDeathEvent(const tf::DamagePacket& damage) {
    tf::DamagePacket IDied;
    IDied.header = "damage";
    IDied.died = true;
    IDied.playerId = ownPlayer.playerID;
    IDied.playerName = packet.playerName;
    IDied.hitById = damage.hitById;
    IDied.hitByName = damage.hitByName;
    IDied.damage = 0; // we don't need to set damage, we died
    client.send(IDied);

    ownPlayer.setPosition(spawnPoints[std::rand() % 8]);
    ownPlayer.setHealth(100);
    ownPlayer.giveFullAmmo();
    ownPlayer.setScore(damage.hitByName, tf::Scores{100, 1, 0});
    ownPlayer.setScore(packet.playerName, Scores{0,0,1});
    deathClock.restart();


}
}