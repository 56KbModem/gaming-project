//
// Created by Nathan Hoekstra on 2019-01-02.
//

#ifndef TOPFORCE_TEST_MENU_HPP
#define TOPFORCE_TEST_MENU_HPP

#include "../topforce.hpp"
#include "menu.hpp"
#include "../action.hpp"

namespace tf{
    namespace gui{
        class main_menu {
        private:
            sf::RenderWindow & window;
            sf::Music menu_sound;
            sf::SoundBuffer selection_buffer;
            sf::Sound selection_music;
            enum class menus {
                main,
                play,
                settings,
            };
            menus active_menu;
        public:
            main_menu(sf::RenderWindow & window);
            game_mode run();
        };
    }
}



#endif //TOPFORCE_TEST_MENU_HPP
