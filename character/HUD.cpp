//
// Created by marcd on 21-1-2019.
//

#include "HUD.hpp"

namespace tf {
HUD::HUD(sf::RenderWindow &window, sf::View& view) :
    MoveableScreenObject(window),
    currentAmmo(30),
    totalAmmo(90),
    currentHealth(100),
    clipSize(30),
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
    if (currentAmmo <= 10) {
        ammoText.setFillColor(sf::Color::Red);
    }
    if (currentHealth <= 30) {
        healthText.setFillColor(sf::Color::Red);
    }
}

void HUD::configText() {
    // Size + color
    ammoText.setCharacterSize(24);
    healthText.setCharacterSize(24);
    reloadText.setCharacterSize(24);
    reloadText.setFillColor(sf::Color::Red);
    // set font
    ammoText.setFont(font);
    healthText.setFont(font);
    reloadText.setFont(font);
    // this text does not change over time, that's why it is initialized already
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

    // position
    sf::Vector2f viewCenter = view.getCenter();
    healthText.setPosition(viewCenter.x + 750, viewCenter.y + 350);
    ammoText.setPosition(viewCenter.x + 750, viewCenter.y + 400);
    reloadText.setPosition(viewCenter.x + 700, viewCenter.y + 450);
}

void HUD::decreaseHealth(const int &amount) {
    currentHealth -= amount;
}

void HUD::decreaseAmmo(const int &amount) {
    if (currentAmmo >= 0) {
        currentAmmo -= amount;
    }
}

void HUD::reload() {
    /*return if all ammo equals 0 or if current magazine is already full*/
    if (currentAmmo != clipSize) {
        if (totalAmmo != 0) {
            int needed = clipSize - currentAmmo;
            if (needed < totalAmmo) {
                totalAmmo -= needed;
                currentAmmo += needed;
            } else {
                currentAmmo += totalAmmo;
                totalAmmo = 0;
            }
        }
    }
}
} // namespace tf
