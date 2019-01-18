//
// Created by marcd on 17-1-2019.
//

#ifndef TOPFORCE_WINDOW_SETTINGS_H
#define TOPFORCE_WINDOW_SETTINGS_H

#define IMAGE_FOLDER "assets/images/"
#include "../topforce.hpp"
namespace tf {
class topforce_window : public sf::RenderWindow {
private:
    sf::Image image;
    sf::Texture cursor_texture;
    sf::Sprite cursor;
public:
    topforce_window();
    void set_window_icon(const std::string &filename);
    void set_cursor_icon(const std::string &filename);
    void set_sprite_pos(const sf::Vector2f &pos);
    sf::Sprite get_cursor_sprite();
};
}


#endif //TOPFORCE_WINDOW_SETTINGS_H
