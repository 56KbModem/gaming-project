//
// Created by marcd on 21-1-2019.
//

#include "HUD.hpp"

namespace tf {
HUD::HUD(sf::RenderWindow &window, sf::View& view) :
    MoveableScreenObject(window),
    currentAmmo(30),
    clipSize(30),
    totalAmmo(90),
    currentHealth(100),
    view(view)
    {
        if (!font.loadFromFile(FONT)) {
            TF_ERROR("Unable to load HUD font");
        }
        configText();
    }

void HUD::updateText() {
    ammoText.setString("Ammo: " + std::to_string(currentAmmo) + '/' + std::to_string(totalAmmo));
    healthText.setString("HP: " + std::to_string(currentHealth) + "/100");
}

void HUD::checkAmmo() {
    if (currentAmmo < 10) {
        ammoText.setFillColor(sf::Color::Red);
    }
    if (currentHealth < 30) {
        healthText.setFillColor(sf::Color::Red);
    }
}

void HUD::configText() {
    // Size + color
    ammoText.setCharacterSize(24);
    healthText.setCharacterSize(24);
    reloadText.setCharacterSize(24);
    reloadText.setFillColor(sf::Color::Red);

    ammoText.setFont(font);
    healthText.setFont(font);
    reloadText.setFont(font);

    reloadText.setString("Press R to reload");
}

void HUD::draw() const {
    if (currentAmmo < 5) {
        window.draw(reloadText);
    }
    window.draw(ammoText);
    window.draw(healthText);
    window.draw(reloadText);
}

void HUD::update() {
    checkAmmo();
    updateText();

    // update position relative to view
    sf::Vector2f viewCenter = view.getCenter();
    healthText.setPosition(viewCenter.x + 750, viewCenter.y + 350);
    ammoText.setPosition(viewCenter.x + 750, viewCenter.y + 400);
    reloadText.setPosition(viewCenter.x + 700, viewCenter.y + 450);
}

void HUD::decreaseHealth(const int &amount) {
    currentHealth -= amount;
}

void HUD::decreaseAmmo(const int &amount) {
    currentAmmo -= amount;
}

void HUD::reload() {

}
} // namespace tf
