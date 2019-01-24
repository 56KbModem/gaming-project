//
// Created by Nathan Hoekstra on 2019-01-23.
//

#include "ImageManager.hpp"

namespace tf{
ImageManager::ImageManager() {
    texture[0].loadFromFile(PATH + "main_menu_bg.jpg");
    texture[1].loadFromFile(PATH + "soldier1_machine.png");
    texture[2].loadFromFile(PATH + "soldier1_reload.png");
    icon.loadFromFile(PATH + "topforce_icon.png");
}
ImageManager& ImageManager::getInstance() {
    static ImageManager Instance;
    return Instance;
}

const sf::Texture& ImageManager::getMenuBackground() {
    return texture[0];
}

const sf::Texture& ImageManager::getSoldierStationary() {
    return texture[1];
}

const sf::Texture& ImageManager::getSoldierWalking() {
    return texture[2];
}

const sf::Uint8* ImageManager::getWindowIcon() {
    return icon.getPixelsPtr();
}
}