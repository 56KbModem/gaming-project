//
// Created by Nathan Hoekstra on 2019-01-22.
//

#include "SoundManager.hpp"

namespace tf {
constexpr const char* SoundManager::fileNames[];

SoundManager::SoundManager() {
    mainMenu.openFromFile(PATH + "gui/menu_sound.wav");
    backgroundNoise.openFromFile(PATH + "background_noise.wav");

    sound[0].setVolume(20);

    for (unsigned i = 1; i < buffer.size(); i++) {
        buffer[i].loadFromFile(fileNames[i - 1]);
        sound[i].setBuffer(buffer[i]);
    }
}

SoundManager& SoundManager::getInstance() {
    static SoundManager Instance;
    return Instance;
}

void SoundManager::setWeapon(const std::string &weaponFile) {
    if(!buffer[0].loadFromFile(PATH + weaponFile)){
        TF_ERROR("Unable to load file: {}",weaponFile);
    }
    sound[0].setBuffer(buffer[0]);
}

void SoundManager::play(const tf::Sounds &sounds, const float volume, bool loop) {
    auto index = static_cast<unsigned>(sounds);

    switch (sounds) {
        case Sounds::VoiceReloading: {
            int random = std::rand() % (10 - 7 + 1) + 7;
            sound[random].play();
            sound[random].setVolume(volume);
            return;
        }
        case Sounds::StopNoise:
            backgroundNoise.stop();
            return;
        case Sounds::StopMenu:
            mainMenu.stop();
            return;
        case Sounds::Menu:
            mainMenu.play();
            mainMenu.setLoop(loop);
            return;
        case Sounds::BackgroundNoise:
            backgroundNoise.play();
            backgroundNoise.setLoop(loop);
            return;
        default:
            sound[index].play();
            sound[index].setVolume(volume);
    }
}
}