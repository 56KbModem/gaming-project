//
// Created by Nathan Hoekstra on 2019-01-21.
//

#include "FreeForAll.hpp"

namespace tf{ namespace gamemode{
    FreeForAll::FreeForAll(tf::TopforceWindow & window, const std::string & mapName):
        GameMode(window, mapName)
    {
        mSObjects.push_back(&ownPlayer);
        sObjects.push_back(&level);
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
            for (const auto& obj : sObjects) {
                obj->draw();
            }

            for (const auto& obj : mSObjects) {
                obj->draw();
                obj->update();
            }

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