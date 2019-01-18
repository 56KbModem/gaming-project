//
// Created by Marc on 1/15/2019.
//

#ifndef TOPFORCE_SCREENOBJECT_HPP
#define TOPFORCE_SCREENOBJECT_HPP

#include "../topforce.hpp"

namespace tf {
    class ScreenObject {
    protected:
        sf::RenderWindow& window;
    public:
        ScreenObject(sf::RenderWindow& window);
        virtual void draw() const = 0;
    };
    bool intersects(sf::Shape& shape, sf::Shape& other);
}

#endif //TOPFORCE_SCREENOBJECT_HPP
