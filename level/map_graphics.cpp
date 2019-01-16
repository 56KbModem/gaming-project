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

    bool map_graphics::check_collision(tf::character &character) {
        auto & layers = map.getLayers();
        for(auto & layer : layers){
            if(layer->getType() == tmx::Layer::Type::Object){
                for(auto& object : layer->getLayerAs<tmx::ObjectGroup>().getObjects()){
                    if(layer->getName() == "Intersectable"){
                        auto pos = object.getPosition();
                        if(pos.x == character.get_position().x){
                            TF_INFO("Object colided!");
                        }
                    }
                }
            }
        }
    }
}}