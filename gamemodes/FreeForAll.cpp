//
// Created by Nathan Hoekstra on 2019-01-21.
//

#include "FreeForAll.hpp"

namespace tf{ namespace gamemode{

FreeForAll::FreeForAll(tf::TopforceWindow & window, const std::string & mapName, sf::IpAddress & serverIp):
    GameMode(window, mapName, serverIp),
    sendThread(&FreeForAll::send, this)
{
    view.setSize(1920.f, 1080.f);
    sendThread.detach();
}
FreeForAll::~FreeForAll() {}

void FreeForAll::run() {
    GameMode::packet.PlayerId = ownPlayer.playerID;
    GameMode::packet.playerName = sf::IpAddress::getLocalAddress().toString();

    GameMode::damagePacket.hitById = ownPlayer.playerID;
    GameMode::damagePacket.damage = 15;

    // ---- Free-For-All gameloop ----
    while (window.isOpen()) {
        // Recieve Server packets
        GameMode::serverPacket = client.getLastPacket();

        GameMode::ownPlayer.decreaseHealth(client.getDamage().damage);

        if(serverPacket.firing){
            soundManager.play(tf::Sounds::FireWeapon);
        }
        //Cursor position calculation
        GameMode::window.setSpritePosition();
        GameMode::window.setRotation(ownPlayer.getRotation());

        if (!GameMode::playerExists(serverPacket)) {
            GameMode::enemies.push_back(Character(window, serverPacket.PlayerId));
        }
        // set position, rotation, shooting ... etc
        GameMode::setEnemyParams(serverPacket);

        GameMode::window.clear(sf::Color::Black);
        GameMode::window.setView(view);

        //Cursor position calculation
        GameMode::window.setSpritePosition();

        // Draw objects
        GameMode::level.draw();
        GameMode::ownPlayer.draw();
        GameMode::ownPlayer.update();
        for (const auto& enemy : GameMode::enemies) {
            enemy.draw();
        }

        GameMode::sendDamage();

        GameMode::ownPlayer.setTime(GameMode::client.getTime());
        GameMode::window.draw(GameMode::window.getCursorSprite());
        GameMode::window.display();

        // Handle pollEvents
        sf::Event event;
        while (GameMode::window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                GameMode::window.close();
            }
        }
    }
}

void FreeForAll::send(){
    while(true) {
        packet.rotation = ownPlayer.getRotation();
        packet.position = ownPlayer.getPosition();
        client.send(packet);
        packet.firing = false;
        sf::sleep(sf::milliseconds(5));
    }
}
}}