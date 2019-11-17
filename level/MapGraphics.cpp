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
    for (const auto & hitBox : hitBoxes) {
        sf::RectangleShape rectangle(sf::Vector2f(hitBox.width, hitBox.height));
        hitBoxVisuals.push_back(std::move(rectangle));
    }

    for (unsigned i = 0; i < hitBoxVisuals.size(); i++) {
        hitBoxVisuals[i].setPosition(hitBoxes[i].left, hitBoxes[i].top);
        hitBoxVisuals[i].setFillColor(sf::Color(0, 255, 0, 100));
    }
#endif
}

void MapGraphics::setHitBoxes(const std::vector<tmx::Object> &objects) {
    for (const auto& object : objects) {
        const tmx::FloatRect& rect = object.getAABB();
        hitBoxes.emplace_back(sf::FloatRect(rect.left, rect.top, rect.width, rect.height));
    }
}

void MapGraphics::parseMapLayers() {
    const auto& mapLayers = map.getLayers();

    for (unsigned i = 0; i < mapLayers.size(); i++) {
        if (mapLayers[i]->getType() != tmx::Layer::Type::Object) {
            layers.push_back(std::make_unique<MapLayer>(map, i));
        }
        else {
            const std::vector<tmx::Object> &objects = mapLayers[i]
            		->getLayerAs<tmx::ObjectGroup>()
                    .getObjects();
            setHitBoxes(objects);
        }
    }
}

void MapGraphics::draw() const {
    for (const auto& layer : layers) {
        window.draw(*layer);
    }
#if DEBUG
    for (const auto & hitBox : hitBoxVisuals){
        window.draw(hitBox);
    }
#endif
}

bool MapGraphics::intersects(tf::Player &character) {
    for (const auto &hitBox : hitBoxes) {
        if (hitBox.intersects(character.getBounds())) {
            return true;
        }
    }
    return false;
}

const std::vector<sf::FloatRect>& MapGraphics::getHitBoxes(){
    return hitBoxes;
}
}}
