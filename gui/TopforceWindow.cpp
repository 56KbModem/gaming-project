//
// Created by marcd on 17-1-2019.
//

#include "TopforceWindow.hpp"
namespace tf {
    TopforceWindow::TopforceWindow()
    {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;
        sf::RenderWindow::create(sf::VideoMode(1920, 1080), "Topforce", sf::Style::Titlebar | sf::Style::Close, settings);
        sf::RenderWindow::setVerticalSyncEnabled(true);
        sf::RenderWindow::setFramerateLimit(60);
    }

    void TopforceWindow::setWindowIcon() {
        sf::RenderWindow::setIcon(512, 512, imageManager.getWindowIcon());
    }

    void TopforceWindow::setCursorIcon(const std::string &filename) {
        sf::RenderWindow::setMouseCursorVisible(false);
        cursorTexture.loadFromFile("assets/images/crosshair.png");
        cursor = sf::Sprite(cursorTexture);
        cursor.setScale(0.3f,0.3f);
    }

    void TopforceWindow::setSpritePosition() {
        sf::Vector2i position = sf::Mouse::getPosition(*this);
        sf::Vector2f worldPos = mapPixelToCoords(position);
        cursor.setPosition(sf::Vector2f(worldPos.x - 20, worldPos.y - 20));
    }

    sf::Sprite TopforceWindow::getCursorSprite() {
        return cursor;
    }
}