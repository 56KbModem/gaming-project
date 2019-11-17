//
// Created by Cris on 19-1-2019.
//

#include "Weapon.hpp"

namespace tf {
Weapon::Weapon(sf::RenderWindow & window, const std::vector<sf::FloatRect> & levelHitBoxes, std::vector<tf::Character> & enemies):
    window(window),
    levelHitBoxes(levelHitBoxes),
    enemies(enemies),
    bulletHit(sf::Vector2f(1, 1)),
    weaponLocation(sf::Vector2f(10, 10))
{
    sf::FloatRect bounds = bulletHit.getGlobalBounds();
    bulletHit.setOrigin(bounds.width / 2, bounds.height /2);
    bulletHit.setFillColor(sf::Color::Cyan);
    weaponLocation.setOrigin(bounds.width / 2, bounds.height /2);
    weaponLocation.setFillColor(sf::Color::Blue);
    soundManager.setWeapon("weap_g3.wav");
}

void Weapon::shoot(const sf::Vector2f &position, const float rotation, tf::HUD &hud, sf::Uint32 &playerID){
    if(shootClock.getElapsedTime().asMilliseconds() > 100){
        if(hud.hasAmmo()) {
            emptyMag = false;
            hud.decreaseAmmo(1);
            soundManager.play(tf::Sounds::FireWeapon);
            drawShootLine(position, rotation, playerID);
            shootClock.restart();
        }
        else if(emptyMag == 0 && !hud.hasAmmo()){
            emptyMag = true;
            soundManager.play(tf::Sounds::EmptyWeapon);
        }
    }
}

void Weapon::drawShootLine(const sf::Vector2f &position, const float rotation, sf::Uint32 &playerID) {
    shootLine[0] = sf::Vertex(getWeaponLocation());
    bulletHit.setPosition(getWeaponLocation());
    weaponLocation.setPosition(position);
    bool hit = false;

    while (!hit) {
        moveBullet(rotation);
        bounds = bulletHit.getGlobalBounds();
        for (auto &enemy : enemies){
            if (!enemy.getBounds().intersects(bounds)) {
                continue;
            }
            hit = true;
            playerID = enemy.playerID;
            setBulletCollisionPoint(bulletHit.getPosition());
        }
        for (auto &hitBox : levelHitBoxes){
            if (!hitBox.intersects(bounds)) {
                continue;
            }
            hit = true;
            setBulletCollisionPoint(bulletHit.getPosition());
        }
    }
    shootLine[1] = sf::Vertex(bulletHit.getPosition());
    window.draw(bulletHit);
    window.draw(shootLine, 2, sf::Lines);
}

void Weapon::moveBullet(const float rotation){
    bulletHit.move(static_cast<float>(cos((rotation + 180) * (PI / 180)) *- 15),
                   static_cast<float>(sin((rotation + 180) * (PI / 180)) *- 15));
}

void Weapon::setWeaponLocation (const sf::Vector2f &position, const float rotation){
    weaponLocation.setPosition(position);
    weaponLocation.move(static_cast<float>(cos((rotation + 212) * (PI / 180)) *- 20),
                        static_cast<float>(sin((rotation + 212) * (PI / 180)) *- 20));
#if DEBUG
    window.draw(weaponLocation);
#endif
}

sf::Vector2f Weapon::getWeaponLocation(){
    return weaponLocation.getPosition();
}

sf::Vector2f Weapon::getBulletCollisionPoint() {
    return bulletCollisionPoint;
}

void Weapon::setBulletCollisionPoint(const sf::Vector2f &bulletColPoint) {
    bulletCollisionPoint = bulletColPoint;
}

}