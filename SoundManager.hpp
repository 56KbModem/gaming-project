//
// Created by Nathan Hoekstra on 2019-01-22.
//

#ifndef TOPFORCE_SOUNDMANAGER_HPP
#define TOPFORCE_SOUNDMANAGER_HPP

#include "topforce.hpp"

namespace tf{
class SoundManager {
private:
    SoundManager();
    const std::string PATH =  "assets/sounds/";
    sf::SoundBuffer buffer[5];
    sf::Sound sound[5];
    sf::Music music;
public:
    static SoundManager & getInstance();
    void setWeapon(const std::string & weaponFile);
    void fireWeapon();
    void uiSelect();
    void uiHover();
    void menuSound(bool loop);
    void stopMenuSound();
    void emptyWeapon();
    void reloadWeapon();
};
}

#endif //TOPFORCE_SOUNDMANAGER_HPP
