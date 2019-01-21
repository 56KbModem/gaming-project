//
// Created by Nathan Hoekstra on 2019-01-21.
//

#include "FreeForAll.hpp"

namespace tf{ namespace gamemode{
    FreeForAll::FreeForAll(tf::TopforceWindow & window, const std::string & mapName):
        GameMode(window, mapName)
    {
        view.setSize(1920.f, 1080.f);
    }
    void FreeForAll::run() {
        // ---- Free-For-All gameloop ----
        while (window.isOpen())
        {
            window.clear(sf::Color::Black);
            window.setView(view);
            //Cursor position calculation
            sf::Vector2i position = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(position);
            window.setSpritePosition(worldPos);
            // Draw objects
            level.draw();
            ownPlayer.update();
            ownPlayer.draw();
            window.draw(window.getCursorSprite());
            window.display();
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
        }
    }
}}