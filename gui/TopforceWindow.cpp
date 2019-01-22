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

    void TopforceWindow::setWindowIcon(const std::string &filename) {
        image.loadFromFile(IMAGE_FOLDER + filename);
        sf::RenderWindow::setIcon(512, 512, image.getPixelsPtr());
    }

    void TopforceWindow::setCursorIcon(const std::string &filename) {
        sf::RenderWindow::setMouseCursorVisible(true);
        cursorTexture.loadFromFile(IMAGE_FOLDER + filename);
        cursor = sf::Sprite(cursorTexture);
        cursor.setScale(0.5f,0.5f);
    }

    void TopforceWindow::setSpritePosition(const sf::Vector2f &pos) {
        cursor.setPosition(pos);
    }

    sf::Sprite TopforceWindow::getCursorSprite() {
        return cursor;
    }
}