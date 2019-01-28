
#include "Player.hpp"

namespace tf {
Player::Player(tf::TopforceWindow &window, const int &playerID, sf::View & view, const std::vector<sf::FloatRect> & levelHitboxes, std::vector<tf::Character> & enemies):
    Character(window, playerID),
    view(view),
    levelHitboxes(levelHitboxes),
    myWeapon(window, levelHitboxes, enemies),
    hud(window, view)
{
    view.setCenter(mySprite.getPosition());
}

void Player::draw() const {
    hud.draw();
    tf::Character::draw();
}

void Player::setTexture(const Texture & texture){
    if(texture == Texture::Walking && mySprite.getTexture() != &imageManager.getTexture(Texture::Walking)){
        mySprite.setTexture(imageManager.getTexture(Texture::Walking), true);
    }
    if(texture == Texture::Stationary && mySprite.getTexture() != &imageManager.getTexture(Texture::Stationary)){
        mySprite.setTexture(imageManager.getTexture(Texture::Stationary), true);
    }
}

void Player::move(const sf::Vector2f & position) {
    mySprite.move(position);
    hitbox.setPosition(mySprite.getPosition().x -25, mySprite.getPosition().y - 25);
    for(auto & hitbox : levelHitboxes){
        if(hitbox.intersects(getBounds())){
            mySprite.move(-position);
        }
    }
    view.setCenter(mySprite.getPosition());
}

void Player::update(){
    for(auto & action : actions) {
        action();
    }
    hud.update();
}

void Player::shoot(const float & rotation){
    myWeapon.shoot(mySprite.getPosition(), mySprite.getRotation(), hud);
}

void Player::lookAtMouse() {
    sf::Vector2f curPos = mySprite.getPosition();
    sf::Vector2i position = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(position);
    float dx = curPos.x - worldPos.x;
    float dy = curPos.y - worldPos.y;
    float rotation = float((atan2(dy, dx)) * 180 / PI) + 180;
    myWeapon.setWeaponLocation(curPos, getRotation());
    mySprite.setRotation(rotation);
}

void Player::setTime(const tf::TimePacket & packet) {
    hud.setTime(packet);
}
} // End namespace tf
