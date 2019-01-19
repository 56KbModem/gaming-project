#include "../abstracts/MoveableScreenObject.hpp"
#include "weapon.hpp"

#ifndef TOPFORCE_CHARACTER_HPP
#define TOPFORCE_CHARACTER_HPP

#define PLAYER "assets/images/soldier1_machine.png"
#define RELOAD "assets/images/soldier1_reload.png"
#define WEAPONG3 "assets/sounds/weap_g3_slst_2.wav"
#define PI 3.14159265

namespace tf{
class Character: public tf::MoveableScreenObject {
private:
    sf::Sprite mySprite;
    sf::Texture stationary;
    sf::Texture reloading;
    sf::View & view;
    std::vector<sf::FloatRect> levelHitboxes;
    sf::RectangleShape hitbox;
    tf::Weapon myWeapon;
public:
    Character(sf::RenderWindow &window, sf::View & view, const std::vector<sf::FloatRect> & levelHitboxes);

    void draw() const override;
    void move(const sf::Vector2f & position) override;
    void setTexture(const std::string & texture);
    void shoot();
    void lookAtMouse();
    sf::FloatRect getBounds();
    sf::Vector2f getPosition();
};

}

#endif //TOPFORCE_CHARACTER_HPP