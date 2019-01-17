//
// Created by Nathan Hoekstra on 2019-01-15.
//

#include <iostream>
#include "map_graphics.hpp"

#define PATH "assets/levels/"

namespace tf{namespace level {
map_graphics::map_graphics(const std::string &map_name, sf::RenderWindow &window) :
        screen_object(window)
    {
        if (!map.load(PATH + map_name)) {
            TF_ERROR("Unable to load map {}", map_name);
        }
        parse_map_layers();
#if DEBUG
        for (const auto & hitbox : hitboxes) {
            hitbox_visuals.push_back(sf::RectangleShape(sf::Vector2f(hitbox.width,hitbox.height)));
        }
        int index = 0;
        for (auto & hitbox : hitbox_visuals) {
            hitbox.setPosition(hitboxes[index].left, hitboxes[index].top);
            hitbox.setFillColor(sf::Color(0, 255, 0, 100)); // Set hitbox visuals to green with low opacity
            index++;
        }
#endif
    }

void map_graphics::set_hitboxes(const std::vector<tmx::Object>& objects) {
    for (const auto& object : objects) {
        tmx::FloatRect rect = object.getAABB();
        hitboxes.emplace_back(sf::FloatRect(rect.left, rect.top, rect.width, rect.height));
    }
}

void map_graphics::parse_map_layers() {
    const auto& map_layers = map.getLayers();
    unsigned int layer_level = 0;
    for (const auto& map_layer : map_layers) {
        if (map_layer->getType() != tmx::Layer::Type::Object) {
            layers.push_back(std::make_unique<MapLayer>(map, layer_level));
        }
        else {
            const std::vector<tmx::Object>& objects = map_layer->getLayerAs<tmx::ObjectGroup>().getObjects();
            set_hitboxes(objects);
        }
        layer_level++;
    }
}

void map_graphics::draw() const {
    for (const auto& layer : layers) {
        window.draw(*layer);
    }
#if DEBUG
    for (const auto & hitbox : hitbox_visuals){
        window.draw(hitbox);
    }
#endif
}

bool map_graphics::intersects(tf::character &character) {
    for (const auto &hitbox : hitboxes) {
        if (hitbox.intersects(character.get_bounds())) {
            return true;
        }
    }
    return false;
}
}}
