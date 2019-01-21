//
// Created by Nathan Hoekstra on 2019-01-21.
//

#ifndef TOPFORCE_FREEFORALL_HPP
#define TOPFORCE_FREEFORALL_HPP

#include "../topforce.hpp"
#include "../gui/TopforceWindow.hpp"
#include "../level/MapGraphics.hpp"
#include "../character/Character.hpp"
#include "../Action.hpp"
namespace tf{ namespace gamemode{
    class FreeForAll {
    private:
        tf::TopforceWindow & window;
        tf::level::MapGraphics level;
        sf::View view;
        tf::Character ownPlayer;
    public:
        FreeForAll(tf::TopforceWindow & window, const std::string & mapName);
        void run();
    };
}}


#endif //TOPFORCE_FREEFORALL_HPP
