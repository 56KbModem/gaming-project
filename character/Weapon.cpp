//
// Created by Cris on 19-1-2019.
//

#include "Weapon.hpp"

namespace tf {
    Weapon::Weapon(sf::RenderWindow & window, const std::vector<sf::FloatRect> & levelHitboxes):
    window(window),
    levelHitboxes(levelHitboxes),
<<<<<<< HEAD
    bulletHit(sf::Vector2f(1, 1)),
=======
    bulletHit(sf::Vector2f(5, 5)),
>>>>>>> fc7bc053ed8688c9789980a37ae6571858e8ec3d
    weaponLocation(sf::Vector2f(10, 10))
    {
    sf::FloatRect bounds = bulletHit.getGlobalBounds();
    bulletHit.setOrigin(bounds.width / 2, bounds.height /2);
    bulletHit.setFillColor(sf::Color::Cyan);
    weaponLocation.setOrigin(bounds.width / 2, bounds.height /2);
    weaponLocation.setFillColor(sf::Color::Blue);
    soundManager.setWeapon("weap_g3.wav");
}

void Weapon::shoot(const sf::Vector2f & position, const float & rotation, tf::HUD & hud){
    if(shootClock.getElapsedTime().asMilliseconds() > 100){
        if(hud.hasAmmo()) {
            emptyMag = 0;
            hud.decreaseAmmo(1);
            soundManager.play(tf::Sounds::FireWeapon);
            drawShootLine(position, rotation);
            shootClock.restart();
        }
        else if(emptyMag == 0 && !hud.hasAmmo()){
            emptyMag = 1;
            soundManager.play(tf::Sounds::EmptyWeapon);
        }
    }
}

void Weapon::drawShootLine(const sf::Vector2f &position, const float & rotation) {
    shootLine[0] = sf::Vertex(getWeaponLocation());
    bulletHit.setPosition(getWeaponLocation());
    weaponLocation.setPosition(position);
    bool hit = 0;
    while(!hit) {
        moveBullet(rotation);
        bounds = bulletHit.getGlobalBounds();
        for (auto &hitbox : levelHitboxes){
            if (hitbox.intersects(bounds)){
#if DEBUG
                TF_INFO("object hit!");
#endif
                hit = 1;
                break;
            }
        }
    }
    shootLine[1] = sf::Vertex(bulletHit.getPosition());
    window.draw(bulletHit);
    window.draw(shootLine, 2, sf::Lines);
}

void Weapon::moveBullet(const float & rotation){
    bulletHit.move(cos((rotation + 180) * (PI / 180)) *- 15, (sin((rotation + 180) * (PI / 180)) *- 15));
}

void Weapon::setWeaponLocation(const sf::Vector2f & position, const float & rotation){
    weaponLocation.setPosition(position);
    weaponLocation.move(cos((rotation + 212) * (PI / 180)) *- 20, (sin((rotation + 212) * (PI / 180)) *- 20));
#if DEBUG
    window.draw(weaponLocation);
#endif
}

sf::Vector2f Weapon::getWeaponLocation(){
    return weaponLocation.getPosition();
}

}