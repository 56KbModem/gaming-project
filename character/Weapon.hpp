#include "../topforce.hpp"

#ifndef TOPFORCE_WEAPON_HPP
#define TOPFORCE_WEAPON_HPP

#define WEAPONG3 "assets/sounds/weap_g3_slst_2.wav"

namespace tf{
class Weapon {
private:
    sf::SoundBuffer selectionBuffer;
    sf::Sound weaponSound;
    sf::Clock shootClock;
    sf::RectangleShape shootLine;
    sf::RenderWindow window;
public:
    Weapon(sf::RenderWindow &window);
    void shoot(const sf::Vector2f & position, const float & rotation);
    void drawShootLine(const sf::Vector2f & position, const float & rotation);



};
}

#endif //TOPFORCE_WEAPON_HPP
