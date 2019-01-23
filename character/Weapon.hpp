#include "../topforce.hpp"
#include "../character/HUD.hpp"

#ifndef TOPFORCE_WEAPON_HPP
#define TOPFORCE_WEAPON_HPP
#define PI 3.14159265

namespace tf{
class Weapon {
private:
    sf::Clock shootClock;
    sf::Vertex shootLine[2];
    sf::RenderWindow & window;
    std::vector<sf::FloatRect> levelHitboxes;
    sf::RectangleShape bulletHit;
    sf::FloatRect bounds;
    tf::SoundManager & soundManager = tf::SoundManager::getInstance();
    bool emptyMag = 0;
public:
    Weapon(sf::RenderWindow &window, const std::vector<sf::FloatRect> & levelHitboxes);
    void shoot(const sf::Vector2f & position, const float & rotation, tf::HUD & hud);
    void drawShootLine(const sf::Vector2f & position, const float & rotation);
    void moveBullet(const float & rotation);

};
}

#endif //TOPFORCE_WEAPON_HPP
