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
FreeForAll::~FreeForAll() {
    stopThread = true;
}

void FreeForAll::run() {
    GameMode::packet.PlayerId = ownPlayer.playerID;
    GameMode::packet.playerName = sf::IpAddress::getLocalAddress().toString();

    GameMode::damagePacket.hitById = ownPlayer.playerID;
    GameMode::damagePacket.damage = 15;
    GameMode::damagePacket.hitByName = packet.playerName;
    GameMode::damagePacket.died = false; // we haven't died


    // Create random seed based on current time
    std::srand(std::time(nullptr));
    ownPlayer.setPosition(spawnPoints[std::rand() % 8]);

    // ---- Free-For-All gameloop ----
    while (window.isOpen() && !ownPlayer.isTimeOver()) {
        // Recieve Server packets
        GameMode::serverPacket = client.getLastPacket();
        damage = client.getDamage();

        for (auto& action : actions) {
            action();
        }

        //Cursor position calculation
        GameMode::window.setSpritePosition();
        GameMode::window.setRotation(ownPlayer.getRotation());

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
        for (auto& enemy : GameMode::enemies) {
            enemy.draw();
            if(serverPacket.firing && serverPacket.PlayerId == enemy.playerID){
                sf::Vector2f tmpLocation = enemy.getWeaponPosition();
                enemy.setShootLine(tmpLocation, enemy.firePosition);
                enemy.drawShootline();
            }
        }

        GameMode::sendDamage();

        GameMode::ownPlayer.setTime(GameMode::client.getTime());
        GameMode::window.draw(GameMode::window.getCursorSprite());
        GameMode::window.display();

        // Handle pollEvents
        sf::Event event;
        while (GameMode::window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                packet.firing = false;
                tf::PlayerPacket leave={"leave"};
                client.send(leave);
                GameMode::window.close();
            }
        }
        packet.firing = false;
    }
    window.setView(window.getDefaultView());
}

void FreeForAll::send(){
    while(!stopThread) {
        packet.rotation = ownPlayer.getRotation();
        packet.position = ownPlayer.getPosition();
        packet.firePos = ownPlayer.getBulletCollisionPoint();
        client.send(packet);
        sf::sleep(sf::milliseconds(5));
    }
}
}}