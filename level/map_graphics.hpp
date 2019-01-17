//
// Created by Nathan Hoekstra on 2019-01-15.
//

#ifndef TOPFORCE_MAP_LOADER_HPP
#define TOPFORCE_MAP_LOADER_HPP

#include "../topforce.hpp"
#include "../abstracts/screen_object.hpp"
#include <tmxlite/Map.hpp>
#include "SFMLOrthogonalLayer.hpp"
#include "../character/character.hpp"

namespace tf { namespace level {
class map_graphics : public tf::screen_object {
    private:
        tmx::Map map;
        std::vector<std::unique_ptr<MapLayer>> layers;
        std::vector<sf::FloatRect> hitboxes;
#if DEBUG
        std::vector<sf::RectangleShape> hitbox_visuals;
#endif
        void set_hitboxes(const std::vector<tmx::Object>& objects);
        void parse_map_layers();
    public:
        map_graphics(const std::string &map_name, sf::RenderWindow &window);
        void draw() const override;
        bool intersects(tf::character &character);
    };

}}

#endif //TOPFORCE_MAP_LOADER_HPP
