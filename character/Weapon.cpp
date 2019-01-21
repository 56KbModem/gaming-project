//
// Created by Cris on 19-1-2019.
//

#include "Weapon.hpp"

namespace tf {
    Weapon::Weapon(sf::RenderWindow & window, const std::vector<sf::FloatRect> & levelHitboxes):
    window(window),
    levelHitboxes(levelHitboxes),
    bulletHit(sf::Vector2f(10, 10))
    {

    if (!selectionBuffer.loadFromFile(WEAPONG3)) {
        TF_ERROR("Failed to load audio file {}", WEAPONG3);
    }
    sf::FloatRect bounds = bulletHit.getGlobalBounds();
    bulletHit.setOrigin(bounds.width /2, bounds.height /2);
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
    for(auto & hitbox : levelHitboxes) {
        if (hitbox.intersects(bounds)) {
            TF_INFO("object hit!");
        } else {
            moveBullet(rotation);
            bounds = bulletHit.getGlobalBounds();
        }
    }

    window.draw(bulletHit);
    window.draw(shootLine, 2, sf::Lines);
}

void Weapon::moveBullet(const float & rotation){
    std::cout << "position bullet: " << bulletHit.getPosition().x << ' ' << bulletHit.getPosition().y << '\n';
    bulletHit.move(cos(rotation * PI /180) * -3, sin(rotation * PI / 180 * -3));
    }

}