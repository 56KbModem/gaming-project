//
// Created by Cris on 19-1-2019.
//

#include "Weapon.hpp"

namespace tf {
    Weapon::Weapon(sf::RenderWindow &window)
    {

    if (!selectionBuffer.loadFromFile(WEAPONG3)) {
        TF_ERROR("Failed to load audio file {}", WEAPONG3);
    }
    weaponSound.setBuffer(selectionBuffer);
    shootLine.setOutlineColor(sf::Color::Black);
    shootLine.setFillColor(sf::Color::Black);
}

void Weapon::shoot(const sf::Vector2f & position, const float & rotation){
    if(shootClock.getElapsedTime().asMilliseconds() > 100){
        weaponSound.play();
        drawShootLine(position, rotation);
        shootClock.restart();
    }
}

void Weapon::drawShootLine(const sf::Vector2f &position, const float &rotation) {
#if DEBUG
        TF_INFO("Drawing shooting line. ");
        std::cout << "position " << position.x << ' ' << position.y << '\n';
        std::cout << "rotation " << rotation << '\n';
#endif
        shootLine.setPosition(position);
        shootLine.setRotation(rotation);
        shootLine.setSize(sf::Vector2f{100, 100});
        window.draw(shootLine);
    }

}