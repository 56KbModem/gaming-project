//
// Created by marcd on 21-1-2019.
//

#ifndef TOPFORCE_HUD_H
#define TOPFORCE_HUD_H
#define FONT "assets/fonts/BankGothicMediumBT.ttf"

#include "../abstracts/MoveableScreenObject.hpp"
#include "../Topforce.hpp"

namespace tf {
class HUD : public MoveableScreenObject {
private:
    int currentAmmo, totalAmmo, currentHealth;
    const int clipSize;
    sf::Font font;
    sf::View& view;

    sf::Text ammoText;
    sf::Text healthText;
    sf::Text reloadText;
    tf::SoundManager & soundManager = tf::SoundManager::getInstance();
    sf::Text timeLeft;

    void configText();
    void checkHUD();
    void updateText();
public:
    HUD(sf::RenderWindow& window, sf::View& view);

    void update() override;
    void draw() const override;
    void setTime(const tf::TimePacket& packet);
    void setHealth(const int & health);
    void decreaseAmmo(const int& amount);
    void decreaseHealth(const int& amount);
    void setAmmo(const int &currentAmmo, const int &totalAmmo);

    void reload();
    bool hasAmmo();
    int getHealth();
};
} // namespace tf

#endif //TOPFORCE_HUD_H