//
// Created by Nathan Hoekstra on 2019-01-22.
//

#ifndef TOPFORCE_SOUNDMANAGER_HPP
#define TOPFORCE_SOUNDMANAGER_HPP

#include <string>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include "Log.hpp"

namespace tf{
enum class Sounds {
    FireWeapon,
    UIHover,
    UISelect,
    EmptyWeapon,
    ReloadWeapon,
    StopMenu,
    Menu
};

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
    void play(const tf::Sounds& sounds, const float & volume = 100, bool loop = false);
};

}

#endif //TOPFORCE_SOUNDMANAGER_HPP
