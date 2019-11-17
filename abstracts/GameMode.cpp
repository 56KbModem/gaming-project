//
// Created by marcd on 21-1-2019.
//

#include "GameMode.hpp"

namespace tf {
GameMode::GameMode(tf::TopforceWindow &window, const std::string &mapName, sf::IpAddress & serverIp):
    window(window),
    level(mapName, window),
    client(serverIp),
    ownPlayer(window, sf::IpAddress::getLocalAddress().toInteger(), view, level.getHitBoxes(), enemies, packet)
{
    view.setSize(1920.f, 1080.f);
    ownPlayer.setScore(sf::IpAddress::getLocalAddress().toString());
}

GameMode::~GameMode() = default;

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
        if (enemy.playerID != packet.PlayerId) {
            continue;
        }

        enemy.setPosition(packet.position);
        enemy.setRotation(packet.rotation);
        enemy.firePosition = packet.firePos;
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
    tf::DamagePacket iDied;
    iDied.header = "damage";
    iDied.died = true;
    iDied.playerId = ownPlayer.playerID;
    iDied.playerName = packet.playerName;
    iDied.hitById = damage.hitById;
    iDied.hitByName = damage.hitByName;
    iDied.damage = 0; // we don't need to set damage, we died
    client.send(iDied);

    ownPlayer.setPosition(spawnPoints[std::rand() % 8]);
    ownPlayer.setHealth(100);
    ownPlayer.giveFullAmmo();
    ownPlayer.setScore(damage.hitByName, tf::Scores{100, 1, 0});
    ownPlayer.setScore(packet.playerName, tf::Scores{0,0,1});
    deathClock.restart();
}
}