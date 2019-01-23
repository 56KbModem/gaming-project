#include "../abstracts/MoveableScreenObject.hpp"
#include "Weapon.hpp"
#include "../Action.hpp"
#include "HUD.hpp"

#ifndef TOPFORCE_CHARACTER_HPP
#define TOPFORCE_CHARACTER_HPP
#define PI 3.14159265

namespace tf{
class Character: public tf::MoveableScreenObject {
private:
    sf::Sprite mySprite;
    sf::View & view;
    std::vector<sf::FloatRect> levelHitboxes;
    sf::RectangleShape hitbox;
    tf::Weapon myWeapon;
    sf::Vector2f currentPosition;
    tf::HUD hud;
    tf::ImageManager & imageManager = tf::ImageManager::getInstance();
    Action actions[8] = {Action([&](){currentPosition = getPosition(); lookAtMouse();} ),
                        Action(sf::Keyboard::W, [&](){setTexture("RELOADING"); move( sf::Vector2f{ 0.0f, -5.0f } );}),
                        Action(sf::Keyboard::A, [&](){setTexture("RELOADING"); move( sf::Vector2f{ -5.0f, 0.0f } );}),
                        Action(sf::Keyboard::S, [&](){setTexture("RELOADING"); move( sf::Vector2f{ 0.0f, 5.0f } ); }),
                        Action(sf::Keyboard::D, [&](){setTexture("RELOADING"); move( sf::Vector2f{ 5.0f, 0.0f } ); }),
                        Action(sf::Keyboard::R, [&](){hud.reload();}),
                        Action(sf::Mouse::Left, [&](){if(currentPosition == getPosition()){ shoot(getRotation());} }),
                        Action([&](){return currentPosition == getPosition();}, [&](){setTexture("STATIONARY");})
    };
public:
    Character(sf::RenderWindow &window, sf::View & view, const std::vector<sf::FloatRect> & levelHitboxes);

    void draw() const override;
    void move(const sf::Vector2f & position);
    void update() override;

    void setTexture(const std::string & texture);
    void shoot(const float & rotation);
    void lookAtMouse();
    sf::FloatRect getBounds();
    sf::Vector2f getPosition();
    void setPosition(sf::Vector2f & position);
    float getRotation();
    void setRotation(float & rotation);
};

}

#endif //TOPFORCE_CHARACTER_HPP