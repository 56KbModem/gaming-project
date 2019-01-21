//
// Created by Cris on 19-1-2019.
//

#include "Weapon.hpp"

namespace tf {
    Weapon::Weapon(sf::RenderWindow & window, const std::vector<sf::FloatRect> & levelHitboxes):
    window(window),
    levelHitboxes(levelHitboxes)
    {

    if (!selectionBuffer.loadFromFile(WEAPONG3)) {
        TF_ERROR("Failed to load audio file {}", WEAPONG3);
    }
    weaponSound.setBuffer(selectionBuffer);
}

void Weapon::shoot(const sf::Vector2f & position){
    if(shootClock.getElapsedTime().asMilliseconds() > 100){
        weaponSound.play();
        drawShootLine(position);
        shootClock.restart();
    }
}

void Weapon::drawShootLine(const sf::Vector2f &position) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePosition);
        shootLine[0] = sf::Vertex(sf::Vector2f(position.x, position.y));
        shootLine[1] = sf::Vertex(sf::Vector2f(worldPos.x + 30, worldPos.y + 30));
        window.draw(shootLine, 2, sf::Lines);
    }
}