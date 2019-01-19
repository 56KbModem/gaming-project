//
// Created by Cris on 19-1-2019.
//

#include "weapon.hpp"

namespace tf {
    Weapon::Weapon()
    {

    if (!selectionBuffer.loadFromFile(WEAPONG3)) {
        TF_ERROR("Failed to load audio file {}", WEAPONG3);
    }
    weaponSound.setBuffer(selectionBuffer);
}

void Weapon::shoot(){
    if(shootClock.getElapsedTime().asMilliseconds() > 100){
        weaponSound.play();
        shootClock.restart();
    }
}

}