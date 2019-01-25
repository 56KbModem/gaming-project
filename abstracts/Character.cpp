//
// Created by marcd on 25-1-2019.
//

#include "Character.hpp"

namespace tf {

Character::Character(tf::TopforceWindow &window, const int &playerID):
    tf::MoveableScreenObject(window),
    playerID(playerID)
{
    mySprite.setTexture(imageManager.getTexture(tf::Texture::EnemyStationary));
    mySprite.setPosition(1700.0, 375.0);
    sf::FloatRect bounds = mySprite.getGlobalBounds();
    mySprite.setOrigin(bounds.width / 2, bounds.height / 2);
    hitbox.setSize({55.0f, 55.0f});
    hitbox.setFillColor(sf::Color(0,0,0,0));
#if DEBUG
    hitbox.setFillColor(sf::Color(255,0,0,100));
#endif
}

void Character::setTexture(const Texture & texture){
    if(texture == Texture::EnemyWalking && mySprite.getTexture() != &imageManager.getTexture(Texture::EnemyWalking)){
        mySprite.setTexture(imageManager.getTexture(Texture::EnemyWalking), true);
    }
    if(texture == Texture::EnemyStationary && mySprite.getTexture() != &imageManager.getTexture(Texture::EnemyStationary)){
        mySprite.setTexture(imageManager.getTexture(Texture::EnemyStationary), true);
    }
}

void Character::update() {
}

void Character::draw() const {
    window.draw(mySprite);
#if DEBUG
    window.draw(hitbox);
#endif
}

sf::FloatRect Character::getBounds() {
    return hitbox.getGlobalBounds();
}

sf::Vector2f Character::getPosition() {
    return mySprite.getPosition();
}

void Character::setPosition(const sf::Vector2f &position) {
    mySprite.setPosition(position);
    hitbox.setPosition(mySprite.getPosition().x -25, mySprite.getPosition().y - 25);
}

float Character::getRotation() {
    return mySprite.getRotation();
}

void Character::setRotation(const float &rotation) {
    mySprite.setRotation(rotation);
}
}
