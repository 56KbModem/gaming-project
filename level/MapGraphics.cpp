//
// Created by Nathan Hoekstra on 2019-01-15.
//

#include "MapGraphics.hpp"

#define PATH "assets/levels/"

namespace tf{namespace level{
    MapGraphics::MapGraphics(const std::string &map_name, sf::RenderWindow& window):
        ScreenObject(window)
    {
        if(!map.load(PATH + map_name)){
            TF_ERROR("Unable to load map {}",map_name);
        }
        ground          = std::make_unique<MapLayer>(map, Layers::Ground);
        decorations     = std::make_unique<MapLayer>(map, Layers::Decorations);
        intersectables  = std::make_unique<MapLayer>(map, Layers::Intersectable);
    }
    void MapGraphics::draw() const {
        window.draw(*ground);
        window.draw(*decorations);
        window.draw(*intersectables);
    }
    sf::FloatRect MapGraphics::get_bounds() {
        return intersectables->getGlobalBounds();
    }
}}