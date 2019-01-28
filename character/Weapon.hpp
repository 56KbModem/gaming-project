#include "../Topforce.hpp"
#include "../character/HUD.hpp"
#include "../abstracts/Character.hpp"

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
    std::vector<tf::Character> & enemies;
    sf::RectangleShape bulletHit;
    sf::RectangleShape weaponLocation;
    sf::FloatRect bounds;
    tf::SoundManager & soundManager = tf::SoundManager::getInstance();
    bool emptyMag = 0;
public:
    Weapon(sf::RenderWindow &window, const std::vector<sf::FloatRect> & levelHitboxes, std::vector<tf::Character> & enemies);
    void shoot(const sf::Vector2f & position, const float & rotation, tf::HUD & hud, sf::Uint32 & playerID);
    void drawShootLine(const sf::Vector2f & position, const float & rotation, sf::Uint32 & playerID);
    void moveBullet(const float & rotation);
    void setWeaponLocation(const sf::Vector2f & position, const float & rotation);
    sf::Vector2f getWeaponLocation();
};
}

#endif //TOPFORCE_WEAPON_HPP
