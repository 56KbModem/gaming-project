#include "../abstracts/moveable_screen_object.hpp"

#ifndef TOPFORCE_CHARACTER_HPP
#define TOPFORCE_CHARACTER_HPP

#define PLAYER "assets/images/soldier1_machine.png"
#define RELOAD "assets/images/soldier1_reload.png"
#define PI 3.14159265

namespace tf{
class character: public tf::moveable_screen_object {
private:
    sf::Sprite mySprite;
    sf::Texture stationary;
    sf::Texture reloading;
    sf::View & view;
public:
    character(sf::RenderWindow &window, sf::View & view);

    void draw() const override;
    void move(const sf::Vector2f & position) override;

    void lookAtMouse();
    //void move(sf::View &view) override;
    void setTexture(const std::string & texture);
    sf::Vector2f getPosition();
};

}

#endif //TOPFORCE_CHARACTER_HPP