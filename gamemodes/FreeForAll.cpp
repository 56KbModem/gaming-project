//
// Created by Nathan Hoekstra on 2019-01-21.
//

#include "FreeForAll.hpp"

namespace tf{ namespace gamemode{
    FreeForAll::FreeForAll(tf::TopforceWindow & window, const std::string & mapName, sf::IpAddress & serverIp):
        GameMode(window, mapName),
        client(53000,serverIp,53000),
        enemy(window,view,level.getHitboxes())
    {
        view.setSize(1920.f, 1080.f);
    }
    void FreeForAll::run() {
        // DEBUG STUFF
        packet.PlayerId = 2;
        packet.playerName = "DebugPlayer2";
        // ---- Free-For-All gameloop ----
        while (window.isOpen())
        {
            // Recieve server packets
            if(client.receive() == sf::Socket::Done){
                serverPacket = client.getLastPacket();
            }
            window.clear(sf::Color::Black);
            window.setView(view);
            //Cursor position calculation
            sf::Vector2i position = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(position);
            window.setSpritePosition(worldPos);

            // Set enemy position
            enemy.setPosition(serverPacket.position);
            enemy.setRotation(serverPacket.rotation);

            // Draw objects
            level.draw();
            ownPlayer.update();
            ownPlayer.draw();
            enemy.draw();
            window.draw(window.getCursorSprite());
            window.display();

            // Send own position to server
            packet.rotation = ownPlayer.getRotation();
            packet.position = ownPlayer.getPosition();
            client.send(packet);
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
        }
    }
}}