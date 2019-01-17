//
// Created by marcd on 17-1-2019.
//

#include "topforce_window.h"
namespace tf {
    topforce_window::topforce_window()
    {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;
        sf::RenderWindow::create(sf::VideoMode(1920, 1080), "Topforce", sf::Style::Titlebar | sf::Style::Close, settings);
        sf::RenderWindow::setVerticalSyncEnabled(true);
        sf::RenderWindow::setFramerateLimit(60);
    }

    void topforce_window::set_window_icon(const std::string &filename) {
        image.loadFromFile(IMAGE_FOLDER + filename);
        sf::RenderWindow::setIcon(512, 512, image.getPixelsPtr());
    }

    void topforce_window::set_cursor_icon(const std::string &filename) {
        sf::RenderWindow::setMouseCursorVisible(false);
        cursor_texture.loadFromFile(IMAGE_FOLDER + filename);
        cursor = sf::Sprite(cursor_texture);
        cursor.setScale(0.5f,0.5f);
    }

    void topforce_window::set_cursor_sprite(const sf::Vector2f &pos) {
        cursor.setPosition(pos);
    }

    sf::Sprite topforce_window::get_cursor_sprite() {
        return cursor;
    }
}