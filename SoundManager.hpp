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
	Menu,
    StopMenu,
    Damage,
    Spawn,
    VoiceReloading,
    BackgroundNoise,
    StopNoise
};

class SoundManager {
private:
    SoundManager();

    static constexpr const char* fileNames[] = {
    		"gui/ui_hover.wav",
		    "gui/ui_select.wav",
		    "weap_dryfire.wav",
		    "weap_reload.wav",
		    "damage_sound.wav",
		    "spawn.wav",
		    "reloading_coverme.wav",
		    "reloading_coverme_scream.wav",
		    "reloading_scream.wav",
		    "reloading_normal.wav"
    };

    const std::string PATH =  "assets/sounds/";
    std::array<sf::SoundBuffer, 11> buffer;
	std::array<sf::Sound, 11> sound;
    sf::Music mainMenu;
    sf::Music backgroundNoise;
public:
    SoundManager(const SoundManager & SoundManager) = delete;
    void operator=(const SoundManager& SoundManager) = delete;
    static SoundManager& getInstance();
    void setWeapon(const std::string & weaponFile);
    void play(const tf::Sounds &sounds, float volume = 100, bool loop = false);
};

}

#endif //TOPFORCE_SOUNDMANAGER_HPP
