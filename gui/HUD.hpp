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
    int currentAmmo, totalAmmo, currentHealth, minutes, seconds;
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
    void setHealth(int health);
    void decreaseAmmo(int amount);
    void decreaseHealth(int amount);
    void setAmmo(int currentAmmo, int totalAmmo);
    bool isTimeOver();
    void reload();
    bool hasAmmo();
    int getHealth();
};
} // namespace tf

#endif //TOPFORCE_HUD_H
