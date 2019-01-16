//
// Created by Marc on 1/15/2019.
//

#ifndef TOPFORCE_SCREENOBJECT_HPP
#define TOPFORCE_SCREENOBJECT_HPP

#include "../topforce.hpp"

namespace tf {
    class screen_object {
    protected:
        sf::RenderWindow& window;
    public:
        screen_object(sf::RenderWindow& window);
        virtual void draw() const = 0;
    };
    bool intersects(sf::Shape& shape, sf::Shape& other);
}

#endif //TOPFORCE_SCREENOBJECT_HPP
