//
// Created by crisv on 16-1-2019.
//

#ifndef TOPFORCE_MOVEABLE_SCREEN_OBJECT_HPP
#define TOPFORCE_MOVEABLE_SCREEN_OBJECT_HPP

#include "screen_object.hpp"

namespace tf{
class moveable_screen_object : public screen_object {
public:
    moveable_screen_object(sf::RenderWindow & window);
    virtual void move(const sf::Vector2f & position) = 0;
};
}


#endif //TOPFORCE_MOVEABLE_SCREEN_OBJECT_HPP
