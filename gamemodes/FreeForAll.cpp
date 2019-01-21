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
        sf::Vector2f currentPosition;

        Action actions[] = {
            Action([](){return true;}, [&](){currentPosition = ownPlayer.getPosition(); ownPlayer.lookAtMouse();} ),
            Action(sf::Keyboard::W, [&](){ownPlayer.setTexture("RELOADING"); ownPlayer.move( sf::Vector2f{ 0.0f, -5.0f } );}),
            Action(sf::Keyboard::A, [&](){ownPlayer.setTexture("RELOADING"); ownPlayer.move( sf::Vector2f{ -5.0f, 0.0f } );}),
            Action(sf::Keyboard::S, [&](){ownPlayer.setTexture("RELOADING"); ownPlayer.move( sf::Vector2f{ 0.0f, 5.0f } ); }),
            Action(sf::Keyboard::D, [&](){ownPlayer.setTexture("RELOADING"); ownPlayer.move( sf::Vector2f{ 5.0f, 0.0f } ); }),
            Action(sf::Mouse::Left, [&](){if(currentPosition == ownPlayer.getPosition()){ ownPlayer.shoot();}}),
            Action([&](){return currentPosition == ownPlayer.getPosition();}, [&](){ownPlayer.setTexture("STATIONARY");})
        };

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
            ownPlayer.draw();
            for (auto & action : actions){
                action();
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