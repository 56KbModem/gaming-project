//
// Created by crisv on 16-1-2019.
//

#ifndef TOPFORCE_MOVEABLE_SCREEN_OBJECT_HPP
#define TOPFORCE_MOVEABLE_SCREEN_OBJECT_HPP

#include "ScreenObject.hpp"

namespace tf{
class MoveableScreenObject : public ScreenObject {
public:
    MoveableScreenObject(sf::RenderWindow & window);
    virtual void move(const sf::Vector2f & position) = 0;
};
}


#endif //TOPFORCE_MOVEABLE_SCREEN_OBJECT_HPP
