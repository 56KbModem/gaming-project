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
    sf::Clock clock1;
    sf::Clock deathClock;

    sf::Vector2f spawnPoints[] = {sf::Vector2f(3165,1760),
                                  sf::Vector2f(3485,2985),
                                  sf::Vector2f(1845,3150),
                                  sf::Vector2f(1275,2485),
                                  sf::Vector2f(815,1955),
                                  sf::Vector2f(895,480),
                                  sf::Vector2f(1700,370),
                                  sf::Vector2f(2470,2135)
    };
    // Create random seed based on current time
    std::srand(std::time(nullptr));
    ownPlayer.setPosition(spawnPoints[std::rand() % 8]);

    ownPlayer.setScore("Mr.SKiLzZ", tf::Scores{1000, 10, 0});
    ownPlayer.setScore("Kaazerne", tf::Scores{200, 2, 10});
    ownPlayer.setScore("Cris", tf::Scores{0, 0, 2});

    // ---- Free-For-All gameloop ----
    while (window.isOpen()) {
        // Recieve Server packets
        GameMode::serverPacket = client.getLastPacket();

        GameMode::ownPlayer.decreaseHealth(client.getDamage().damage);
        if(ownPlayer.getHealth() < 0){
            ownPlayer.setPosition(spawnPoints[std::rand() % 8]);
            ownPlayer.setHealth(100);
            ownPlayer.giveFullAmmo();
            deathClock.restart();
        }
        if(deathClock.getElapsedTime().asMilliseconds() < 2000 ){
            ownPlayer.setHealth(100);
        }

        if(serverPacket.firing && clock1.getElapsedTime().asMilliseconds() > 100){
            soundManager.play(tf::Sounds::FireWeapon);
            clock1.restart();
        }
        //Cursor position calculation
        GameMode::window.setSpritePosition();
        GameMode::window.setRotation(ownPlayer.getRotation());

        if (!GameMode::playerExists(serverPacket) && serverPacket.PlayerId != 0) {
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
        for (auto& enemy : GameMode::enemies) {
            enemy.draw();
            if(serverPacket.firing && serverPacket.PlayerId == enemy.playerID){
                sf::Vector2f tmpLocation = enemy.getPosition();
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
                GameMode::window.close();
            }
        }
        packet.firing = false;
    }
}

void FreeForAll::send(){
    while(true) {
        packet.rotation = ownPlayer.getRotation();
        packet.position = ownPlayer.getPosition();
        packet.firePos = ownPlayer.getBulletCollisionPoint();
        client.send(packet);
        sf::sleep(sf::milliseconds(5));
    }
}
}}