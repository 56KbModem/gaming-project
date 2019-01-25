//
// Created by Nathan Hoekstra on 2019-01-23.
//

#include "ImageManager.hpp"

namespace tf{
ImageManager::ImageManager() {
    textureArray[0].loadFromFile(PATH + "main_menu_bg.jpg");
    textureArray[1].loadFromFile(PATH + "soldier1_machine.png");
    textureArray[2].loadFromFile(PATH + "soldier1_reload.png");
    icon.loadFromFile(PATH + "topforce_icon.png");
}

ImageManager& ImageManager::getInstance() {
    static ImageManager Instance;
    return Instance;
}

const sf::Texture& ImageManager::getTexture(const tf::Texture &texture) {
    switch(texture){
        case tf::Texture::MenuBG:
            return textureArray[0];
        case tf::Texture::Stationary:
            return textureArray[1];
        case tf::Texture::Walking:
            return textureArray[2];
    }
}

const sf::Uint8* ImageManager::getWindowIcon() {
    return icon.getPixelsPtr();
}
}