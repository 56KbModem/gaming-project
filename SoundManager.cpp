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
            music.play();
            music.setLoop(loop);
            break;
        case Sounds::StopMenu:
            music.stop();
            break;
    }
}
}