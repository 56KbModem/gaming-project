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

void SoundManager::fireWeapon() {
    sound[0].play();
}

void SoundManager::uiHover() {
    sound[1].play();
}

void SoundManager::uiSelect() {
    sound[2].play();
}

void SoundManager::menuSound(bool loop) {
    music.play();
    music.setLoop(loop);
}

void SoundManager::stopMenuSound() {
    music.stop();
}

void SoundManager::emptyWeapon() {
    sound[3].play();
}

void SoundManager::reloadWeapon() {
    sound[4].play();
}

}