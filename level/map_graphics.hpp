//
// Created by Nathan Hoekstra on 2019-01-15.
//

#ifndef TOPFORCE_MAP_LOADER_HPP
#define TOPFORCE_MAP_LOADER_HPP

#include "../topforce.hpp"
#include "../abstracts/screen_object.hpp"
#include <tmxlite/Map.hpp>
#include "SFMLOrthogonalLayer.hpp"

namespace tf { namespace level {
class map_graphics : public tf::screen_object {
    private:
        tmx::Map map;
        std::unique_ptr<MapLayer> ground;
        std::unique_ptr<MapLayer> decorations;
        std::unique_ptr<MapLayer> intersectables;

        enum Layers {
            Ground,
            Decorations,
            Intersectable
        };
    public:
        map_graphics(const std::string & map_name, sf::RenderWindow& window);
        void draw() const override;
        sf::FloatRect get_global_bounds();
    };

}}

#endif //TOPFORCE_MAP_LOADER_HPP
