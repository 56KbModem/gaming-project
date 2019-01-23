//
// Created by Nathan Hoekstra on 2019-01-23.
//

#ifndef TOPFORCE_IMAGEMANAGER_HPP
#define TOPFORCE_IMAGEMANAGER_HPP

#include "topforce.hpp"

namespace tf{
class ImageManager {
private:
    ImageManager();
    const std::string PATH =  "assets/images/";
    sf::Texture texture[3];
    sf::Image icon;
public:
    static ImageManager & getInstance();
    sf::Texture& getMenuBackground();
    sf::Texture& getSoldierStationary();
    sf::Texture& getSoldierWalking();
    const sf::Uint8* getWindowIcon();
};
}


#endif //TOPFORCE_IMAGEMANAGER_HPP
