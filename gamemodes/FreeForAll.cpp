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
    packet.PlayerId = ownPlayer.playerID;
    packet.playerName = sf::IpAddress::getLocalAddress().toString();

    damagePacket.hitById = ownPlayer.playerID;
    damagePacket.damage = 15;

    // ---- Free-For-All gameloop ----
    while (window.isOpen()) {
        // Recieve Server packets
        serverPacket = client.getLastPacket();

        ownPlayer.decreaseHealth(client.getDamage().damage);

        //Cursor position calculation
        window.setSpritePosition();
        window.setRotation(ownPlayer.getRotation());

        if (!playerExists(serverPacket)) {
            enemies.push_back(Character(window, serverPacket.PlayerId));
        }
        // set position, rotation, shooting ... etc
        setEnemyParams(serverPacket);

        window.clear(sf::Color::Black);
        window.setView(view);

        //Cursor position calculation
        window.setSpritePosition();

        // Draw objects
        level.draw();
        ownPlayer.draw();
        ownPlayer.update();
        for (const auto& enemy : enemies) {
            enemy.draw();
        }

        sf::Uint32 enemyID = ownPlayer.getEnemyID();
        if(enemyID > 0){
            damagePacket.playerId = enemyID;
            client.send(damagePacket);
        }

        ownPlayer.setTime(client.getTime());
        window.draw(window.getCursorSprite());
        window.display();

        // Handle pollEvents
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
}

void FreeForAll::send(){
    while(true) {
        packet.rotation = ownPlayer.getRotation();
        packet.position = ownPlayer.getPosition();
        client.send(packet);
        sf::sleep(sf::milliseconds(5));
    }
}
}}