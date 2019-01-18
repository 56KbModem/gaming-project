//
// Created by Nathan Hoekstra on 2019-01-15.
//

#include <iostream>
#include "MapGraphics.hpp"

#define PATH "assets/levels/"

namespace tf{namespace level {
MapGraphics::MapGraphics(const std::string &mapName, sf::RenderWindow &window) :
        ScreenObject(window)
    {
        if (!map.load(PATH + mapName)) {
            TF_ERROR("Unable to load map {}", mapName);
        }
        parseMapLayers();
#if DEBUG
        for (const auto & hitbox : hitboxes) {
            hitboxVisuals.push_back(sf::RectangleShape(sf::Vector2f(hitbox.width,hitbox.height)));
        }
        int index = 0;
        for (auto & hitbox : hitboxVisuals) {
            hitbox.setPosition(hitboxes[index].left, hitboxes[index].top);
            hitbox.setFillColor(sf::Color(0, 255, 0, 100)); // Set hitbox visuals to green with low opacity
            index++;
        }
#endif
    }

void MapGraphics::setHitboxes(const std::vector<tmx::Object> &objects) {
    for (const auto& object : objects) {
        tmx::FloatRect rect = object.getAABB();
        hitboxes.emplace_back(sf::FloatRect(rect.left, rect.top, rect.width, rect.height));
    }
}

void MapGraphics::parseMapLayers() {
    const auto& mapLayers = map.getLayers();
    unsigned int layerLevel = 0;
    for (const auto& mapLayer : mapLayers) {
        if (mapLayer->getType() != tmx::Layer::Type::Object) {
            layers.push_back(std::make_unique<MapLayer>(map, layerLevel));
        }
        else {
            const std::vector<tmx::Object>& objects = mapLayer->getLayerAs<tmx::ObjectGroup>().getObjects();
            setHitboxes(objects);
        }
        layerLevel++;
    }
}

void MapGraphics::draw() const {
    for (const auto& layer : layers) {
        window.draw(*layer);
    }
#if DEBUG
    for (const auto & hitbox : hitboxVisuals){
        window.draw(hitbox);
    }
#endif
}

bool MapGraphics::intersects(tf::Character &character) {
    for (const auto &hitbox : hitboxes) {
        if (hitbox.intersects(character.getBounds())) {
            return true;
        }
    }
    return false;
}

std::vector<sf::FloatRect> MapGraphics::getHitboxes(){
    return hitboxes;
}
}}
