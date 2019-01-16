//
// Created by Nathan Hoekstra on 2019-01-15.
//

#include <iostream>
#include "map_graphics.hpp"

#define PATH "assets/levels/"

namespace tf{namespace level {
map_graphics::map_graphics(const std::string &map_name, sf::RenderWindow &window) :
        screen_object(window) {
    if (!map.load(PATH + map_name)) {
        TF_ERROR("Unable to load map {}", map_name);
    }
    ground = std::make_unique<MapLayer>(map, Layers::Ground);
    decorations = std::make_unique<MapLayer>(map, Layers::Decorations);
    intersectables = std::make_unique<MapLayer>(map, Layers::Intersectable);
    dingen = std::make_unique<MapLayer>(map, 3);

    const auto& layer = map.getLayers()[3];
    const auto& objects = layer->getLayerAs<tmx::ObjectGroup>().getObjects();

    for (const auto& object : objects) {
        tmx::FloatRect rect = object.getAABB();
        bounds.push_back(sf::FloatRect(rect.left, rect.top, rect.width, rect.height));
    }
}

void map_graphics::draw() const {
    window.draw(*ground);
    window.draw(*decorations);
    window.draw(*intersectables);
}

bool map_graphics::check_collision(tf::character &character) {
    for (const auto& bound : bounds) {
        if (bound.intersects(character.get_bounds())) {
            return true;
        }
    }
    return false;
}
}}
