//
// Created by Marc on 1/15/2019.
//

#include "ScreenObject.hpp"


namespace tf {
    ScreenObject::ScreenObject(sf::RenderWindow& window):
        window(window){}

    bool intersects(sf::Shape& shape, sf::Shape& other) {
        return shape.getGlobalBounds().intersects(other.getGlobalBounds());
    }
}