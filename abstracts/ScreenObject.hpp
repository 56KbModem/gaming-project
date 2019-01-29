//
// Created by Marc on 1/15/2019.
//

#ifndef TOPFORCE_SCREENOBJECT_HPP
#define TOPFORCE_SCREENOBJECT_HPP

#include "../Topforce.hpp"
#include "../gui/TopforceWindow.hpp"

namespace tf {
    class ScreenObject {
    protected:
        sf::RenderWindow & window;
    public:
        ScreenObject(sf::RenderWindow & window);
        virtual void draw() const = 0;
    };
}

#endif //TOPFORCE_SCREENOBJECT_HPP
