//
// Created by marcd on 17-1-2019.
//

#ifndef TOPFORCE_WINDOW_SETTINGS_H
#define TOPFORCE_WINDOW_SETTINGS_H

#include "../Topforce.hpp"
#define PI 3.14159265

namespace tf {
class TopforceWindow : public sf::RenderWindow {
private:
    sf::Texture cursorTexture;
    sf::Sprite cursor;
    tf::ImageManager & imageManager = tf::ImageManager::getInstance();
    float cursorRotation = 0;
public:
    TopforceWindow();
    void setWindowIcon();
    void setCursorIcon(const std::string &filename);
    void setSpritePosition();
    sf::Sprite getCursorSprite();
    void setRotation(const float & rotation);
};
}


#endif //TOPFORCE_WINDOW_SETTINGS_H
