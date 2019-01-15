//
// Created by Nathan Hoekstra on 2019-01-15.
//

#include "map_loader.hpp"

#define PATH "assets/levels/"

namespace tf{namespace level{
    map_loader::map_loader(const std::string &map_name) {
        if(!map.load(PATH + map_name)){
            TF_ERROR("Unable to load map {}",map_name);
        }
        ground = std::make_unique<MapLayer>(map,0);
        decorations = std::make_unique<MapLayer>(map,1);
        intersectables = std::make_unique<MapLayer>(map,2);
    }
    void map_loader::draw(sf::RenderWindow &window) {
        window.draw(*ground);
        window.draw(*decorations);
        window.draw(*intersectables);
    }
    sf::FloatRect map_loader::get_bounds() {
        return intersectables->getGlobalBounds();
    }
}}