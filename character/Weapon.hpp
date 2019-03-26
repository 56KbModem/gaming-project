#include "../Topforce.hpp"
#include "../gui/HUD.hpp"
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
    sf::Vector2f bulletCollisionPoint;
    tf::SoundManager & soundManager = tf::SoundManager::getInstance();
    bool emptyMag = 0;
    
    void drawShootLine(const sf::Vector2f & position, const float & rotation, sf::Uint32 & playerID);
    void moveBullet(const float & rotation);
public:
    Weapon(sf::RenderWindow &window, const std::vector<sf::FloatRect> & levelHitboxes, std::vector<tf::Character> & enemies);
    void shoot(const sf::Vector2f & position, const float & rotation, tf::HUD & hud, sf::Uint32 & playerID);
    void setWeaponLocation(const sf::Vector2f & position, const float & rotation);
    sf::Vector2f getWeaponLocation();
    sf::Vector2f getBulletCollisionPoint();
    void setBulletCollisionPoint(const sf::Vector2f & bulletColPoint);
};
}

#endif //TOPFORCE_WEAPON_HPP
