#include "../abstracts/Character.hpp"
#include "Weapon.hpp"
#include "../Action.hpp"
#include "../gui/HUD.hpp"
#include "../gui/ScoreBoard.hpp"

#ifndef TOPFORCE_PLAYER_HPP
#define TOPFORCE_PLAYER_HPP
#define PI 3.14159265

namespace tf{
class Player: public tf::Character {
private:
    sf::View & view;
    const std::vector<sf::FloatRect>& levelHitBoxes;
    sf::Clock reloadClock;
    tf::Weapon myWeapon;
    sf::Vector2f currentPosition;
    sf::Vector2f bulletCollisionPoint;
    tf::HUD hud;
    tf::ScoreBoard scoreBoard;
    sf::Uint32 enemyID = 0;
    tf::PlayerPacket & playerPacket;
    Action actions[9] = {Action(sf::Keyboard::Tab, [&](){scoreBoard.update();}),
                        Action([&](){currentPosition = getPosition(); lookAtMouse();} ),
                        Action(sf::Keyboard::W, [&](){setTexture(Animation::Walking); move( sf::Vector2f{ 0.0f, -5.0f } );}),
                        Action(sf::Keyboard::A, [&](){setTexture(Animation::Walking); move( sf::Vector2f{ -5.0f, 0.0f } );}),
                        Action(sf::Keyboard::S, [&](){setTexture(Animation::Walking); move( sf::Vector2f{ 0.0f, 5.0f } ); }),
                        Action(sf::Keyboard::D, [&](){setTexture(Animation::Walking); move( sf::Vector2f{ 5.0f, 0.0f } ); }),
                        Action(sf::Keyboard::R, [&](){hud.reload(); reloadClock.restart();}),
                        Action(sf::Mouse::Left, [&](){if(currentPosition == getPosition() && reloadClock.getElapsedTime().asMilliseconds() > 1'000){ shoot(enemyID);} }),
                        Action([&](){return currentPosition == getPosition();}, [&](){setTexture(Animation::Stationary);})
    };

    void setTexture(Animation anim) override;
public:
    Player(tf::TopforceWindow &window, sf::Uint32 playerID, sf::View &view,
            const std::vector<sf::FloatRect> &levelHitBoxes, std::vector<tf::Character> &enemies,
            tf::PlayerPacket &playerPacket);
    ~Player() override = default;

    void draw() const override;
    void update() override;

    void move(const sf::Vector2f & position);
    void shoot(sf::Uint32 & playerID);
    void lookAtMouse();
    sf::Vector2f getBulletCollisionPoint();

    void decreaseHealth(unsigned int damage);
    int getHealth();
    void setHealth(int health);

    void setPosition(const sf::Vector2f& position) override;

    void setScore(const std::string& playerName, const Scores& score = Scores{0, 0, 0});
    void showScoreboard();
    void giveFullAmmo();
    bool isTimeOver();
    sf::Uint32 getEnemyID();
    void setTime(const tf::TimePacket & packet);
};

}

#endif //TOPFORCE_PLAYER_HPP