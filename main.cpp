#include "topforce.hpp"
#include "gui/MainMenu.hpp"
#include "character/Character.hpp"
#include "level/MapGraphics.hpp"
#include "abstracts/ScreenObject.hpp"
#include "gui/TopforceWindow.hpp"

int main(){
    // Setup logger
    tf::Log::init();
#if DEBUG
    TF_WARN("TopForce logger initialized!");
    NETWORK_WARN("Network logger initialized!");
#endif

    tf::TopforceWindow window; // customized window
    window.setWindowIcon("Topforce_icon.png");
    window.setCursorIcon("crosshair.png");

    // ---- Main Menu ----
    tf::GameModes selected_mode;
    tf::gui::MainMenu menu(window);
    selected_mode = menu.run(); // selected_mode indicates which game mode needs to be called

#if DEBUG
    TF_INFO("Chosen game mode: {}", int(selected_mode));
#endif


    // ---- SELECTED GAME MODE SHOULD BE LOADED HERE ----
    //
    //

    // ----- TEST CODE -----
    sf::View view;
    tf::level::MapGraphics firing_range("FiringRange.tmx", window);
    tf::Character player1(window, view, firing_range.getHitboxes());
    view.setSize(1920.f, 1080.f);
    sf::Vector2f currentPosition;

    Action actions[] = {Action([](){return true;}, [&](){currentPosition = player1.getPosition();} ),
                        Action(sf::Keyboard::W, [&](){player1.setTexture("RELOADING"); player1.move( sf::Vector2f{ 0.0f, -5.0f } );}),
                        Action(sf::Keyboard::A, [&](){player1.setTexture("RELOADING"); player1.move( sf::Vector2f{ -5.0f, 0.0f } );}),
                        Action(sf::Keyboard::S, [&](){player1.setTexture("RELOADING"); player1.move( sf::Vector2f{ 0.0f, 5.0f } ); }),
                        Action(sf::Keyboard::D, [&](){player1.setTexture("RELOADING"); player1.move( sf::Vector2f{ 5.0f, 0.0f } ); }),
                        Action(sf::Mouse::Left, [&](){if(currentPosition == player1.getPosition()){ player1.shoot();}}),
                        Action([&](){return currentPosition == player1.getPosition();}, [&](){player1.setTexture("STATIONARY");})
    };
    while (window.isOpen())
    {
        window.clear(sf::Color::Black);
        window.setView(view);
        //Cursor position calculation
        sf::Vector2i position = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(position);
        window.setSpritePosition(worldPos);
        // Draw objects
        firing_range.draw();
        player1.draw();
        player1.lookAtMouse();
        for (auto & action : actions){
            action();
        }
        window.draw(window.getCursorSprite());
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