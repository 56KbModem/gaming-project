//
// Created by marcd on 17-1-2019.
//

#ifndef TOPFORCE_WINDOW_SETTINGS_H
#define TOPFORCE_WINDOW_SETTINGS_H

#include "../Topforce.hpp"

namespace tf {
class TopforceWindow : public sf::RenderWindow {
private:
    sf::Texture cursorTexture;
    sf::Sprite cursor;
    tf::ImageManager & imageManager = tf::ImageManager::getInstance();
public:
    TopforceWindow();
    void setWindowIcon();
    //void setCursorIcon(const std::string &filename);
    void setSpritePosition(const sf::Vector2f &pos);
    sf::Sprite getCursorSprite();
};
}


#endif //TOPFORCE_WINDOW_SETTINGS_H
