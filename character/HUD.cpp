//
// Created by marcd on 21-1-2019.
//

#include "HUD.hpp"
#include <iomanip>
//#include <sstream>
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

void HUD::checkHUD() {
    if (currentHealth < 30) {
        healthText.setFillColor(sf::Color::Red);
    } else {
        healthText.setFillColor(sf::Color::White);
    }
    if (currentAmmo <= 8) {
        ammoText.setFillColor(sf::Color::Red);
    } else {
        ammoText.setFillColor(sf::Color::White);
    }
}

void HUD::configText() {
    // Size + color
    ammoText.setCharacterSize(30);
    healthText.setCharacterSize(30);
    reloadText.setCharacterSize(30);
    timeLeft.setCharacterSize(30);

    ammoText.setFont(font);
    healthText.setFont(font);
    reloadText.setFont(font);
    timeLeft.setFont(font);

    reloadText.setString("Press R to reload");
    reloadText.setFillColor(sf::Color::Red);
}

void HUD::draw() const {
    if (currentAmmo <= 8) {
        window.draw(reloadText);
    }
    window.draw(ammoText);
    window.draw(healthText);
    window.draw(timeLeft);
}

void HUD::update() {
    // update position relative to view
    sf::Vector2f viewCenter = view.getCenter();
    float x = viewCenter.x;
    float y = viewCenter.y;
    healthText.setPosition(x + 650, y + 350);
    ammoText.setPosition(x + 650, y + 400);
    reloadText.setPosition(x + 600, y + 450);
    timeLeft.setPosition(x - 925, y - 525);

    checkHUD();
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
            soundManager.play(tf::Sounds::ReloadWeapon);
        }
    }
}

bool HUD::hasAmmo(){
    return currentAmmo > 0;
}

void HUD::setTime(const tf::TimePacket &packet) {
    TF_INFO("Packet: {}",packet.seconds);
    std::stringstream seconds;
    std::stringstream minutes;
    seconds <<std::setw(2) <<std::setfill('0') <<packet.seconds ;
    minutes <<std::setw(2) <<std::setfill('0') <<packet.minutes;
    timeLeft.setString("Time left: " + minutes.str() + ':' + seconds.str());
}
} // namespace tf
