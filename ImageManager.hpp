//
// Created by Nathan Hoekstra on 2019-01-23.
//

#ifndef TOPFORCE_IMAGEMANAGER_HPP
#define TOPFORCE_IMAGEMANAGER_HPP

#include <string>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace tf{
enum class Texture {
    Stationary,
    Walking,
    MenuBG
};

class ImageManager {
private:
    ImageManager();
    const std::string PATH =  "assets/images/";
    sf::Texture textureArray[3];
    sf::Image icon;
public:
    static ImageManager & getInstance();
    const sf::Texture& getTexture(const tf::Texture& texture);
    const sf::Uint8* getWindowIcon();
};
}


#endif //TOPFORCE_IMAGEMANAGER_HPP
