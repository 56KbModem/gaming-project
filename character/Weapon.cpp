//
// Created by Cris on 19-1-2019.
//

#include "Weapon.hpp"

namespace tf {
    Weapon::Weapon(sf::RenderWindow & window, const std::vector<sf::FloatRect> & levelHitboxes):
    window(window),
    levelHitboxes(levelHitboxes),
    bulletHit(sf::Vector2f(25, 25))
    {

    if (!selectionBuffer.loadFromFile(WEAPONG3)) {
        TF_ERROR("Failed to load audio file {}", WEAPONG3);
    }
    sf::FloatRect bounds = bulletHit.getGlobalBounds();
    bulletHit.setOrigin(bounds.width / 2, bounds.height /2);
    bulletHit.setFillColor(sf::Color::Cyan);
    weaponSound.setBuffer(selectionBuffer);
}

void Weapon::shoot(const sf::Vector2f & position, const float & rotation){
    if(shootClock.getElapsedTime().asMilliseconds() > 100){
        weaponSound.play();
        drawShootLine(position, rotation);
        shootClock.restart();
    }
}

void Weapon::drawShootLine(const sf::Vector2f &position, const float & rotation) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(mousePosition);
    shootLine[0] = sf::Vertex(sf::Vector2f(position.x, position.y));
    shootLine[1] = sf::Vertex(sf::Vector2f(worldPos.x + 30, worldPos.y + 30));
    bulletHit.setPosition(position);
    sf::FloatRect bounds = bulletHit.getGlobalBounds();
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
        window.draw(bulletHit);
        window.display();
    }
    window.draw(bulletHit);
    window.draw(shootLine, 2, sf::Lines);
}

void Weapon::moveBullet(const float & rotation){
#if DEBUG
    TF_INFO("bullet pos X: {} pos Y: {}", bulletHit.getPosition().x, bulletHit.getPosition().y);
#endif
    bulletHit.move(cos((rotation + 180) * (PI / 180)) *- 10, (sin((rotation + 180) * (PI / 180)) *- 10));
}

}