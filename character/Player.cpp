
#include "Player.hpp"

namespace tf {
Player::Player(tf::TopforceWindow &window, const sf::Uint32 playerID, sf::View &view,
                const std::vector<sf::FloatRect> &levelHitBoxes, std::vector<tf::Character> &enemies,
                tf::PlayerPacket &playerPacket):
    Character(window, playerID),
    view(view),
    levelHitBoxes(levelHitBoxes),
    myWeapon(window, levelHitBoxes, enemies),
    hud(window, view),
    scoreBoard(window, view),
    playerPacket(playerPacket)
{
    view.setCenter(mySprite.getPosition());
}

void Player::draw() const {
    hud.draw();
    tf::Character::draw();
}

void Player::setTexture(const Animation anim) {
    static constexpr Animation animations[] = { Animation::Walking, Animation::Stationary };

    for (const auto animation : animations) {
        if (mySprite.getTexture() == &imageManager.getTexture(animation)) {
            continue;
        }
        if (animation == anim) {
            mySprite.setTexture(imageManager.getTexture(animation), true);
        }
    }
}

void Player::move(const sf::Vector2f & position) {
    mySprite.move(position);
    hitbox.setPosition(mySprite.getPosition().x - 25, mySprite.getPosition().y - 25);
    for (auto & hitBox : levelHitBoxes) {
        if (hitBox.intersects(getBounds())) {
            mySprite.move(-position);
        }
    }
    view.setCenter(mySprite.getPosition());
}

void Player::update(){
    for (auto & action : actions) {
        action();
    }
    hud.update();
}

void Player::shoot(sf::Uint32& playerID){
    myWeapon.shoot(mySprite.getPosition(), mySprite.getRotation(), hud, playerID);
    playerPacket.firing = true;
}

void Player::lookAtMouse() {
    sf::Vector2f curPos = mySprite.getPosition();
    sf::Vector2i position = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(position);
    float dx = curPos.x - worldPos.x;
    float dy = curPos.y - worldPos.y;
    float rotation = float((std::atan2(dy, dx)) * 180 / PI) + 180;
    myWeapon.setWeaponLocation(curPos, getRotation());
    mySprite.setRotation(rotation);
}

sf::Vector2f Player::getBulletCollisionPoint(){
    return myWeapon.getBulletCollisionPoint();
}

void Player::decreaseHealth(const unsigned int damage) {
    hud.decreaseHealth(damage);
}

int Player::getHealth() {
    return hud.getHealth();
}

void Player::setHealth (const int health) {
    hud.setHealth(health);
}

void Player::setPosition(const sf::Vector2f &position) {
    Character::setPosition(position);
    view.setCenter(mySprite.getPosition());
}

void Player::setScore(const std::string &playerName, const tf::Scores &score) {
    scoreBoard.setScore(playerName, score);
}

void Player::showScoreboard() {
    scoreBoard.update();
}

void Player::giveFullAmmo() {
    hud.setAmmo(30,90);
}

sf::Uint32 Player::getEnemyID() {
    sf::Uint32 enemy = enemyID;
    enemyID = 0;
    return enemy;
}

void Player::setTime(const tf::TimePacket & packet) {
    hud.setTime(packet);
}

bool Player::isTimeOver() {
    return hud.isTimeOver();
}

} // End namespace tf
