//
// Created by Nathan Hoekstra on 2019-01-02.
//

#include "MainMenu.hpp"

namespace tf{namespace gui{
MainMenu::MainMenu(sf::RenderWindow & window):
        window(window),
        activeMenu(Menus::main)
{
}
GameModes MainMenu::run() {
    auto & soundManager = tf::SoundManager::getInstance();
    Menu main(window.getSize(),std::array<std::string,3>{"Play", "Settings", "Quit"});
    Menu play(window.getSize(),std::array<std::string,4>{"Team Deatmatch", "Search & Destroy", "Free For All", "Back"});
    Menu settings(window.getSize(),std::array<std::string,3>{"Music", "FX", "Back"});
    // Play main MainMenu sound
    soundManager.menuSound(true);
    // Set Action list
    Action actions[] = {
            Action( sf::Keyboard::Up,
                    [&](){
                        if(activeMenu == Menus::main) main.moveUp();
                        if(activeMenu == Menus::play) play.moveUp();
                        if(activeMenu == Menus::settings) settings.moveUp();
#if DEBUG
                        TF_INFO("Move up");
#endif
                        sf::sleep( sf::milliseconds(200));}),
            Action( sf::Keyboard::Down,
                    [&](){
                        if(activeMenu == Menus::main) main.moveDown();
                        if(activeMenu == Menus::play) play.moveDown();
                        if(activeMenu == Menus::settings) settings.moveDown();
#if DEBUG
                        TF_INFO("Move down");
#endif
                        sf::sleep( sf::milliseconds(200));}),
    };
    while (window.isOpen()) {
        window.clear();
        // Draw items
        switch(activeMenu){
            case Menus::main:
                main.draw(window);
                break;
            case Menus::play:
                play.draw(window);
                break;
            case Menus::settings:
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
            soundManager.uiSelect();
            switch(activeMenu){
                case Menus::main:
                    switch(main.getPressedItem()){
                        case 0:
                            //Play
                            activeMenu = Menus::play;
                            break;
                        case 1:
                            //Settings
                            activeMenu = Menus::settings;
                            break;
                        case 2:
                            //Quit
                            window.close();
                            break;
                        default:
                            break;
                    }
                    break;
                case Menus::play:
                    switch(play.getPressedItem()){
                        case 0:
                            //Team Deatmatch
                            soundManager.stopMenuSound();
                            return GameModes::Team_Deathmatch;
                        case 1:
                            //Search & Destroy
                            soundManager.stopMenuSound();
                            return GameModes::Search_and_Destroy;
                        case 2:
                            //Free For All
                            soundManager.stopMenuSound();
                            return GameModes::Free_For_All;
                        case 3:
                            //Back
                            activeMenu = Menus::main;
                            play.reset();
                            break;
                        default:
                            break;
                    }
                    break;
                case Menus::settings:
                    switch(settings.getPressedItem()){
                        case 0:
                            //Music
                            break;
                        case 1:
                            //FX
                            break;
                        case 2:
                            //Back
                            activeMenu = Menus::main;
                            settings.reset();
                            break;
                        default:
                            break;
                    }
                    break;
            }
            sf::sleep( sf::milliseconds(200)); // Sleep for 200ms to counter double keypresses
        }
        // ----- END Menu logic -----
        sf::Event event;
        while( window.pollEvent(event) ){
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
    soundManager.stopMenuSound();
    return GameModes::None;
}
}}
