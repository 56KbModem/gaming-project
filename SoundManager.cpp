//
// Created by Nathan Hoekstra on 2019-01-22.
//

#include "SoundManager.hpp"

namespace tf{
SoundManager::SoundManager() {
    mainMenu.openFromFile(PATH + "gui/menu_sound.wav");
    backgroundNoise.openFromFile(PATH + "background_noise.wav");
    sound[0].setVolume(20);
    buffer[1].loadFromFile(PATH + "gui/ui_hover.wav");
    sound[1].setBuffer(buffer[1]);
    buffer[2].loadFromFile(PATH + "gui/ui_select.wav");
    sound[2].setBuffer(buffer[2]);
    buffer[3].loadFromFile(PATH + "weap_dryfire.wav");
    sound[3].setBuffer(buffer[3]);
    buffer[4].loadFromFile(PATH + "weap_reload.wav");
    sound[4].setBuffer(buffer[4]);
    buffer[5].loadFromFile(PATH + "damage_sound.wav");
    sound[5].setBuffer(buffer[5]);
    buffer[6].loadFromFile(PATH + "spawn.wav");
    sound[6].setBuffer(buffer[6]);
    buffer[7].loadFromFile(PATH + "reloading_coverme.wav");
    sound[7].setBuffer(buffer[7]);
    buffer[8].loadFromFile(PATH + "reloading_coverme_scream.wav");
    sound[8].setBuffer(buffer[8]);
    buffer[9].loadFromFile(PATH + "reloading_scream.wav");
    sound[9].setBuffer(buffer[9]);
    buffer[10].loadFromFile(PATH + "reloading_normal.wav");
    sound[10].setBuffer(buffer[10]);
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

void SoundManager::play(const tf::Sounds& sounds, const float & volume, bool loop) {
    switch (sounds) {
        case Sounds::FireWeapon:
            sound[0].play();
            sound[0].setVolume(volume);
            break;
        case Sounds::UIHover:
            sound[1].play();
            sound[1].setVolume(volume);
            break;
        case Sounds::UISelect:
            sound[2].play();
            sound[2].setVolume(volume);
            break;
        case Sounds::EmptyWeapon:
            sound[3].play();
            sound[3].setVolume(volume);
            break;
        case Sounds::ReloadWeapon:
            sound[4].play();
            sound[4].setVolume(volume);
            break;
        case Sounds::Menu:
            mainMenu.play();
            mainMenu.setLoop(loop);
            break;
        case Sounds::StopMenu:
            mainMenu.stop();
            break;
        case Sounds::Damage:
            sound[5].play();
            sound[5].setVolume(volume);
            break;
        case Sounds::Spawn:
            sound[6].play();
            sound[6].setVolume(volume);
            break;
        case Sounds::VoiceReloading: {
            int random = std::rand() % (10 - 7 + 1) + 7;
            sound[random].play();
            sound[random].setVolume(volume);
            break;
        }
        case Sounds::BackgroundNoise:
            backgroundNoise.play();
            backgroundNoise.setLoop(loop);
            break;
        case Sounds::StopNoise:
            backgroundNoise.stop();
            break;
    }
}
}