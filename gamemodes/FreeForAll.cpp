//
// Created by Nathan Hoekstra on 2019-01-21.
//

#include "FreeForAll.hpp"

namespace tf{ namespace gamemode{
    FreeForAll::FreeForAll(tf::TopforceWindow & window, const std::string & mapName, sf::IpAddress & serverIp):
        GameMode(window, mapName),
        client(53000,serverIp,53000),
        enemy01(window,view,level.getHitboxes()),
        enemy02(window,view,level.getHitboxes()),
        sendThread(&tf::gamemode::FreeForAll::send, this)
    {
        view.setSize(1920.f, 1080.f);
        sendThread.detach();
    }
    void FreeForAll::run() {
        // DEBUG STUFF
        packet.PlayerId = 2;
        packet.playerName = "DebugPlayer1";
       // sf::Thread thread(client.receive());
        // ---- Free-For-All gameloop ----

        while (window.isOpen())
        {

            // Recieve server packets
           // if(client.receive() == sf::Socket::Done){
           serverPacket = client.getLastPacket();
           // }
            window.clear(sf::Color::Black);
            window.setView(view);
            //Cursor position calculation
            sf::Vector2i position = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(position);
            window.setSpritePosition(worldPos);

            // Set enemy position
            if(serverPacket.PlayerId == 1){
                enemy01.setPosition(serverPacket.position);
                enemy01.setRotation(serverPacket.rotation);
            }else if(serverPacket.PlayerId == 3){
                enemy02.setPosition(serverPacket.position);
                enemy02.setRotation(serverPacket.rotation);
            }
            // Draw objects
            level.draw();
            ownPlayer.update();
            ownPlayer.draw();
            enemy01.draw();
            enemy02.draw();
            window.draw(window.getCursorSprite());
            window.display();

            // Send own position to server

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
        }
    }
}}