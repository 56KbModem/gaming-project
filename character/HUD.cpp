//
// Created by marcd on 21-1-2019.
//

#include "HUD.hpp"

namespace tf {
HUD::HUD(sf::RenderWindow &window, sf::View& view) :
    MoveableScreenObject(window),
    currentAmmo(7),
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

void HUD::checkHealth() {
    if (currentHealth < 30) {
        healthText.setFillColor(sf::Color::Red);
    }
}

void HUD::configText() {
    // Size + color
    ammoText.setCharacterSize(24);
    healthText.setCharacterSize(24);
    reloadText.setCharacterSize(24);

    ammoText.setFont(font);
    healthText.setFont(font);
    reloadText.setFont(font);

    reloadText.setString("Press R to reload");
    reloadText.setFillColor(sf::Color::Red);
}

void HUD::draw() const {
    if (currentAmmo <= 8) {
        window.draw(reloadText);
    }
    window.draw(ammoText);
    window.draw(healthText);
}

void HUD::update() {
    // update position relative to view
    sf::Vector2f viewCenter = view.getCenter();
    float x = viewCenter.x;
    float y = viewCenter.y;
    healthText.setPosition(x + 750, y + 350);
    ammoText.setPosition(x + 750, y + 400);
    reloadText.setPosition(x + 700, y + 450);

    checkHealth();
    updateText();
}

void HUD::decreaseHealth(const int &amount) {
    currentHealth -= amount;
}

void HUD::decreaseAmmo(const int &amount) {
    currentAmmo -= amount;
}

void HUD::reload() {
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
            soundManager.reloadWeapon();
        }
    }
}

bool HUD::hasAmmo(){
    return currentAmmo > 0;
}
} // namespace tf
