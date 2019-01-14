//
// Created by Nathan Hoekstra on 2019-01-02.
//

#include "main_menu.hpp"

#define MENU_SOUND "assets/sounds/menu_sound.wav"
#define SELECT_SOUND "assets/sounds/ui_select.wav"

namespace tf{namespace gui{
        main_menu::main_menu(sf::RenderWindow & window):
                window(window),
                active_menu(menus::main)
        {
            if(!menu_sound.openFromFile(MENU_SOUND)){
                TF_ERROR("Failed to load audio file {}",MENU_SOUND);
            }
            if(!selection_buffer.loadFromFile(SELECT_SOUND)){
                TF_ERROR("Failed to load audio file {}",SELECT_SOUND);
            }
            selection_music.setBuffer(selection_buffer);
        }

        game_mode main_menu::run() {
            menu main(window.getSize(),std::array<std::string,3>{"Play", "Settings", "Quit"});
            menu play(window.getSize(),std::array<std::string,4>{"Team Deatmatch", "Search & Destroy", "Free For All", "Back"});
            menu settings(window.getSize(),std::array<std::string,3>{"Music", "FX", "Back"});
            // Play main main_menu sound
            menu_sound.play();
            // Keep playing sound
            menu_sound.setLoop(true);
            // Set action list
            action actions[] = {
                    action( sf::Keyboard::Up,
                            [&](){
                                if(active_menu == menus::main) main.move_up();
                                if(active_menu == menus::play) play.move_up();
                                if(active_menu == menus::settings) settings.move_up();
                                #if DEBUG
                                TF_INFO("Move up");
                                #endif
                                sf::sleep( sf::milliseconds(200));}),
                    action( sf::Keyboard::Down,
                            [&](){
                                if(active_menu == menus::main) main.move_down();
                                if(active_menu == menus::play) play.move_down();
                                if(active_menu == menus::settings) settings.move_down();
                                #if DEBUG
                                TF_INFO("Move down");
                                #endif
                                sf::sleep( sf::milliseconds(200));}),
            };
            while (window.isOpen()) {
                window.clear();
                // Draw items
                switch(active_menu){
                    case menus::main:
                        main.draw(window);
                        break;
                    case menus::play:
                        play.draw(window);
                        break;
                    case menus::settings:
                        settings.draw(window);
                        break;
                }
                //Display all objects
                window.display();

                for(auto & action : actions){
                    action();
                }

                // ----- Menu logic -----
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
                    selection_music.play();
                    switch(active_menu){
                        case menus::main:
                            switch(main.get_pressed_item()){
                                case 0:
                                    //Play
                                    active_menu = menus::play;
                                    break;
                                case 1:
                                    //Settings
                                    active_menu = menus::settings;
                                    break;
                                case 2:
                                    //Quit
                                    window.close();
                                    break;
                                default:
                                    break;
                            }
                            break;
                        case menus::play:
                            switch(play.get_pressed_item()){
                                case 0:
                                    //Team Deatmatch
                                    return game_mode::Team_Deathmatch;
                                case 1:
                                    //Search & Destroy
                                    return game_mode::Search_and_Destroy;
                                case 2:
                                    //Free For All
                                    return game_mode::Free_For_All;
                                case 3:
                                    //Back
                                    active_menu = menus::main;
                                    play.reset();
                                    break;
                                default:
                                    break;
                            }
                            break;
                        case menus::settings:
                            switch(settings.get_pressed_item()){
                                case 0:
                                    //Music
                                    break;
                                case 1:
                                    //FX
                                    break;
                                case 2:
                                    //Back
                                    active_menu = menus::main;
                                    settings.reset();
                                    break;
                                default:
                                    break;
                            }
                            break;
                    }
                    sf::sleep( sf::milliseconds(200)); // Sleep for 200ms to counter double keypresses
                }
                // ----- END menu logic -----
                sf::Event event;
                while( window.pollEvent(event) ){
                    if(event.type == sf::Event::Closed) {
                        window.close();
                    }
                }
            }
            return game_mode::None;
        }
}}
