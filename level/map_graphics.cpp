//
// Created by Nathan Hoekstra on 2019-01-15.
//

#include "map_graphics.hpp"

#define PATH "assets/levels/"

namespace tf{namespace level{
    map_graphics::map_graphics(const std::string &map_name, sf::RenderWindow& window):
        screen_object(window)
    {
        if(!map.load(PATH + map_name)){
            TF_ERROR("Unable to load map {}",map_name);
        }
        ground          = std::make_unique<MapLayer>(map, Layers::Ground);
        decorations     = std::make_unique<MapLayer>(map, Layers::Decorations);
        intersectables  = std::make_unique<MapLayer>(map, Layers::Intersectable);
    }

    void map_graphics::draw() const {
        window.draw(*ground);
        window.draw(*decorations);
        window.draw(*intersectables);
    }

    sf::FloatRect map_graphics::get_global_bounds() {
        return intersectables->getGlobalBounds();
    }
}}