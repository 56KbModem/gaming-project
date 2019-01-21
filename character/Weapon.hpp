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
    sf::Vertex shootLine[2];
    sf::RenderWindow & window;
    std::vector<sf::FloatRect> levelHitboxes;
public:
    Weapon(sf::RenderWindow &window, const std::vector<sf::FloatRect> & levelHitboxes);
    void shoot(const sf::Vector2f & position);
    void drawShootLine(const sf::Vector2f & position);

};
}

#endif //TOPFORCE_WEAPON_HPP
