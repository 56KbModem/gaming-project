//
// Created by marcd on 17-1-2019.
//

#ifndef TOPFORCE_WINDOW_SETTINGS_H
#define TOPFORCE_WINDOW_SETTINGS_H

#define IMAGE_FOLDER "assets/images/"
#include "../topforce.hpp"
namespace tf {
class TopforceWindow : public sf::RenderWindow {
private:
    sf::Image image;
    sf::Texture cursorTexture;
    sf::Sprite cursor;
public:
    TopforceWindow();
    void setWindowIcon(const std::string &filename);
    void setCursorIcon(const std::string &filename);
    void setSpritePosition(const sf::Vector2f &pos);
    sf::Sprite getCursorSprite();
};
}


#endif //TOPFORCE_WINDOW_SETTINGS_H
