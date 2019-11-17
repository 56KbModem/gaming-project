//
// Created by marcd on 25-1-2019.
//

#ifndef TOPFORCE_CHARACTER_HPP
#define TOPFORCE_CHARACTER_HPP

#include "../Topforce.hpp"
#include "MoveableScreenObject.hpp"
#include "../gui/TopforceWindow.hpp"

namespace tf {
class Character : public tf::MoveableScreenObject {
protected:
    sf::Sprite mySprite;
    tf::ImageManager & imageManager = tf::ImageManager::getInstance();
    sf::RectangleShape hitbox;
    sf::Vertex shootLine[2];
    virtual void setTexture(Animation anim);
public:
    Character(tf::TopforceWindow& window, const sf::Uint32 & playerID);
    const sf::Uint32 playerID;
    sf::Vector2f firePosition;

    void draw() const override;
    void update() override;

    sf::FloatRect getBounds();
    sf::Vector2f getPosition();
    sf::Vector2f getWeaponPosition();
    virtual void setPosition(const sf::Vector2f& position);
    float getRotation();
    void setRotation(float rotation);
    void setShootLine(const sf::Vector2f & ownPos, const sf::Vector2f & firePos);
    void drawShootLine() const;
};
}


#endif //TOPFORCE_CHARACTER_HPP
