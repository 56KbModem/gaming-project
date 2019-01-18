//
// Created by Nathan Hoekstra on 2019-01-15.
//

#ifndef TOPFORCE_MAP_LOADER_HPP
#define TOPFORCE_MAP_LOADER_HPP

#include "../topforce.hpp"
#include "../abstracts/ScreenObject.hpp"
#include <tmxlite/Map.hpp>
#include "SFMLOrthogonalLayer.hpp"
#include "../character/Character.hpp"

namespace tf { namespace level {
class MapGraphics : public tf::ScreenObject {
    private:
        tmx::Map map;
        std::vector<std::unique_ptr<MapLayer>> layers;
        std::vector<sf::FloatRect> hitboxes;
#if DEBUG
        std::vector<sf::RectangleShape> hitboxVisuals;
#endif
        void setHitboxes(const std::vector<tmx::Object> &objects);
        void parseMapLayers();
    public:
        MapGraphics(const std::string &mapName, sf::RenderWindow &window);
        void draw() const override;
        bool intersects(tf::Character &character);
        std::vector<sf::FloatRect> getHitboxes();
    };

}}

#endif //TOPFORCE_MAP_LOADER_HPP
