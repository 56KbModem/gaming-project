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
public:
    Weapon();
    void shoot();



};
}

#endif //TOPFORCE_WEAPON_HPP
