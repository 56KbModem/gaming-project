//
// Created by Nathan Hoekstra on 2019-01-15.
//

#ifndef TOPFORCE_MAP_LOADER_HPP
#define TOPFORCE_MAP_LOADER_HPP

#include "../topforce.hpp"
#include <tmxlite/Map.hpp>
#include "SFMLOrthogonalLayer.hpp"

namespace tf{namespace level{
    class map_loader {
    private:
        tmx::Map map;
        std::unique_ptr<MapLayer> ground;
        std::unique_ptr<MapLayer> decorations;
        std::unique_ptr<MapLayer> intersectables;
    public:
        map_loader(const std::string & map_name);
        void draw(sf::RenderWindow & window);
        sf::FloatRect get_bounds(void);
    };

}}

#endif //TOPFORCE_MAP_LOADER_HPP
