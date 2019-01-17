//
// Created by Marc on 1/15/2019.
//

#include "screen_object.hpp"


namespace tf {
    screen_object::screen_object(sf::RenderWindow& window):
        window(window){}

    bool intersects(sf::Shape& shape, sf::Shape& other) {
        return shape.getGlobalBounds().intersects(other.getGlobalBounds());
    }
}