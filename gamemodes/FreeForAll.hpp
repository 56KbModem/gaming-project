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

namespace tf { namespace gamemode {
class FreeForAll : public GameMode {
private:
    std::thread sendThread;
    sf::Clock clock1;
    tf::DamagePacket damage;
    tf::SoundManager & soundManager = tf::SoundManager::getInstance();
    bool stopThread = false;

    Action actions[6] = {
            Action([&]() { return damage.playerId == sf::IpAddress::getLocalAddress().toInteger(); }, [&]() {
                ownPlayer.decreaseHealth(damage.damage); }),
            Action([&]() { return ownPlayer.getHealth() <= 0; }, [&]() {
                handleDeathEvent(damage); }),
            Action([&]() { return deathClock.getElapsedTime().asMilliseconds() < 2000; }, [&]() {
                ownPlayer.setHealth(100); }),
            Action([&]() { return damage.died; }, [&]() {
                ownPlayer.setScore(damage.hitByName, tf::Scores{100, 1, 0});
                ownPlayer.setScore(damage.playerName, tf::Scores{0,0,1});
            }),
            Action([&]() { return serverPacket.firing && clock1.getElapsedTime().asMilliseconds() > 100; }, [&]() {
                soundManager.play(tf::Sounds::FireWeapon); clock1.restart(); }),
            Action([&]() { return !GameMode::playerExists(serverPacket) && serverPacket.PlayerId != 0; }, [&]() {
                GameMode::enemies.push_back(Character(window, serverPacket.PlayerId));
                ownPlayer.setScore(serverPacket.playerName);
            })
    };
public:
    FreeForAll(tf::TopforceWindow & window, const std::string & mapName, sf::IpAddress & serverIp);
    ~FreeForAll();
    void run() override;
    void send();
};
}}


#endif //TOPFORCE_FREEFORALL_HPP
