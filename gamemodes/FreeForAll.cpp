//
// Created by Nathan Hoekstra on 2019-01-21.
//

#include "FreeForAll.hpp"

namespace tf{ namespace gamemode{
    FreeForAll::FreeForAll(tf::TopforceWindow & window, const std::string & mapName, sf::IpAddress & serverIp):
        GameMode(window, mapName),
        client(serverIp),
        enemy01(window,view,level.getHitboxes()),
        enemy02(window,view,level.getHitboxes()),
        sendThread(&tf::gamemode::FreeForAll::send, this)
    {
        view.setSize(1920.f, 1080.f);
        sendThread.detach();
        mSObjects.push_back(&ownPlayer);
        sObjects.push_back(&level);
        sObjects.push_back(&enemy01);
    }
    void FreeForAll::run() {
        // DEBUG STUFF
        packet.PlayerId = 2;
        packet.playerName = "DebugPlayer2";

        // ---- Free-For-All gameloop ----
        while (window.isOpen()) {
            // Recieve server packets
            serverPacket = client.getLastPacket();

            window.clear(sf::Color::Black);
            window.setView(view);

            //Cursor position calculation
            window.setSpritePosition();

            // Set enemy position
            if(serverPacket.PlayerId == 1){
                enemy01.setPosition(serverPacket.position);
                enemy01.setRotation(serverPacket.rotation);
            }else if(serverPacket.PlayerId == 3){
                enemy02.setPosition(serverPacket.position);
                enemy02.setRotation(serverPacket.rotation);
            }
            
            // Draw objects
            for (const auto& obj : sObjects) {
                obj->draw();
            }
            for (const auto& obj : mSObjects) {
                obj->draw();
                obj->update();
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