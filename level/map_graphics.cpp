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

    // --- Fill vector with the level's hitboxes ----
    const auto& layer = map.getLayers()[3];
    const auto& objects = layer->getLayerAs<tmx::ObjectGroup>().getObjects();

    for (const auto& object : objects) {
        tmx::FloatRect rect = object.getAABB();
        hitboxes.push_back(sf::FloatRect(rect.left, rect.top, rect.width, rect.height));
    }
#if DEBUG
    for (const auto & hitbox : hitboxes) {
        hitbox_visuals.push_back(sf::RectangleShape(sf::Vector2f(hitbox.width,hitbox.height)));
    }
    int index = 0;
    for (auto & hitbox : hitbox_visuals) {
        hitbox.setPosition(hitboxes[index].left,hitboxes[index].top);
        hitbox.setFillColor(sf::Color(0,255,0,100)); // Set hitbox visuals to green with low opacity
        index++;
    }
#endif
}

void map_graphics::draw() const {
    window.draw(*ground);
    window.draw(*decorations);
    window.draw(*intersectables);
#if DEBUG
    for (const auto & hitbox : hitbox_visuals){
        window.draw(hitbox);
    }
#endif
}

bool map_graphics::check_collision(tf::character &character) {
    for (const auto& hitbox : hitboxes) {
        if (hitbox.intersects(character.get_bounds())) {
            return true;
        }
    }
    return false;
}
}}
