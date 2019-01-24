//
// Created by Nathan Hoekstra on 2019-01-22.
//

#include "SoundManager.hpp"

namespace tf{
SoundManager::SoundManager() {
    sound[0].setVolume(20);
    buffer[1].loadFromFile(PATH + "gui/ui_hover.wav");
    sound[1].setBuffer(buffer[1]);
    buffer[2].loadFromFile(PATH + "gui/ui_select.wav");
    sound[2].setBuffer(buffer[2]);
    buffer[3].loadFromFile(PATH + "weap_dryfire.wav");
    sound[3].setBuffer(buffer[3]);
    music.openFromFile(PATH + "gui/menu_sound.wav");
    buffer[4].loadFromFile(PATH + "weap_reload.wav");
    sound[4].setBuffer(buffer[4]);
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

void SoundManager::play(const tf::Sounds& sounds, bool loop) {
    Sounds sounds1 = sounds;
    switch (sounds1) {
        case Sounds::FireWeapon:
            sound[0].play();
            break;
        case Sounds::UIHover:
            sound[1].play();
            break;
        case Sounds::UISelect:
            sound[2].play();
            break;
        case Sounds::EmptyWeapon:
            sound[3].play();
            break;
        case Sounds::RealoadWeapon:
            sound[4].play();
            break;
        case Sounds::Menu:
            music.play();
            music.setLoop(loop);
            break;
        case Sounds::StopMenu:
            music.stop();
            break;
    }
}
}