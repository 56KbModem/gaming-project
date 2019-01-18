//
// Created by Nathan Hoekstra on 2019-01-02.
//

#ifndef TOPFORCE_TEST_MENU_HPP
#define TOPFORCE_TEST_MENU_HPP

#include "../topforce.hpp"
#include "Menu.hpp"
#include "../Action.hpp"

namespace tf{
    namespace gui{
        class MainMenu {
        private:
            sf::RenderWindow & window;
            sf::Music menuSound;
            sf::SoundBuffer selection_buffer;
            sf::Sound selectionMusic;
            enum class Menus {
                main,
                play,
                settings,
            };
            Menus activeMenu;
        public:
            MainMenu(sf::RenderWindow & window);
            GameModes run();
        };
    }
}



#endif //TOPFORCE_TEST_MENU_HPP
