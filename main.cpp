#include "topforce.hpp"
#include "gui/main_menu.hpp"
#include "character/character.hpp"
#include "level/map_graphics.hpp"
#include "abstracts/screen_object.hpp"
#include "gui/topforce_window.h"

int main(){
    // Setup logger
    tf::log::init();
#if DEBUG
    TF_WARN("TopForce logger initialized!");
    NETWORK_WARN("Network logger initialized!");
#endif

    tf::topforce_window window; // customized window
    window.set_window_icon("Topforce_icon.png");
    window.set_cursor_icon("crosshair.png");

    // ---- Main menu ----
    tf::game_modes selected_mode;
    tf::gui::main_menu menu(window);
    selected_mode = menu.run(); // selected_mode indicates which game mode needs to be called

#if DEBUG
    TF_INFO("Chosen game mode: {}",int(selected_mode));
#endif


    // ---- SELECTED GAME MODE SHOULD BE LOADED HERE ----
    //
    //

    // ----- TEST CODE -----
    sf::View view;
    tf::character player1(window, view);
    tf::level::map_graphics firing_range("FiringRange.tmx", window);
    view.setSize(1920.f, 1080.f);
    sf::Vector2f currentPosition;

    action Actions[] = {action([](){return true;}, [&](){currentPosition = player1.getPosition();} ),
                        action(sf::Keyboard::W, [&](){player1.setTexture("RELOADING"); player1.move( sf::Vector2f{ 0.0f, -5.0f } );}),
                        action(sf::Keyboard::A, [&](){player1.setTexture("RELOADING"); player1.move( sf::Vector2f{ -5.0f, 0.0f } );}),
                        action(sf::Keyboard::S, [&](){player1.setTexture("RELOADING"); player1.move( sf::Vector2f{ 0.0f, 5.0f } ); }),
                        action(sf::Keyboard::D, [&](){player1.setTexture("RELOADING"); player1.move( sf::Vector2f{ 5.0f, 0.0f } ); }),
                        action(sf::Mouse::Left, [&](){if(currentPosition == player1.getPosition()){ player1.shoot();}}),
                        action([&](){return currentPosition == player1.getPosition();}, [&](){player1.setTexture("STATIONARY");})
    };
    while (window.isOpen())
    {
        window.clear(sf::Color::Black);
        window.setView(view);
        //Cursor position calculation
        sf::Vector2i position = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(position);
        window.set_sprite_pos(worldPos);
        // Draw objects
        firing_range.draw();
        player1.draw();
        player1.lookAtMouse();
        for (auto & action : Actions){
            action();
        }
        window.draw(window.get_cursor_sprite());
        window.display();
        if (firing_range.intersects(player1)) {
            //Some code here
        }
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
    // ---- END TEST CODE -----

#if DEBUG
    TF_INFO("Terminating application!");
#endif
    return 0;
}