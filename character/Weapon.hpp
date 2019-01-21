#include "../topforce.hpp"

#ifndef TOPFORCE_WEAPON_HPP
#define TOPFORCE_WEAPON_HPP

#define WEAPONG3 "assets/sounds/weap_g3_slst_2.wav"
#define PI 3.14159265

namespace tf{
class Weapon {
private:
    sf::SoundBuffer selectionBuffer;
    sf::Sound weaponSound;
    sf::Clock shootClock;
    sf::Vertex shootLine[2];
    sf::RenderWindow & window;
    std::vector<sf::FloatRect> levelHitboxes;
    sf::RectangleShape bulletHit;
public:
    Weapon(sf::RenderWindow &window, const std::vector<sf::FloatRect> & levelHitboxes);
    void shoot(const sf::Vector2f & position, const float & rotation);
    void drawShootLine(const sf::Vector2f & position, const float & rotation);
    void moveBullet(const float & rotation);

};
}

#endif //TOPFORCE_WEAPON_HPP
