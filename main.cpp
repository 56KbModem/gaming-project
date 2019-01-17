#include "topforce.hpp"
#include "gui/main_menu.hpp"
#include "character/character.hpp"
#include "level/map_graphics.hpp"
int main(){
    // Setup logger
    tf::log::init();
    TF_WARN("TopForce logger initialized!");
    NETWORK_WARN("Network logger initialized!");

    // Anti aliasing
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // ---- Window settings ----
    sf::Image window_icon;
    window_icon.loadFromFile("assets/images/Topforce_icon.png");
    sf::RenderWindow window( sf::VideoMode(1920, 1080), "Topforce",sf::Style::Titlebar | sf::Style::Close, settings);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    window.setIcon(512, 512, window_icon.getPixelsPtr());
    // ---- END window settings ----

    // --- Cursor ----
    window.setMouseCursorVisible(false);
    sf::Texture texture;
    texture.loadFromFile("assets/images/crosshair.png");
    sf::Sprite cursor(texture);
    cursor.setScale(0.5f,0.5f);
    // --- END Cursor ----

    // ---- Main menu ----
    tf::game_modes selected_mode;
    tf::gui::main_menu menu(window);
    selected_mode = menu.run(); // selected_mode indicates which game mode needs to be called
#if DEBUG
    TF_INFO("Chosen game mode: {}",int(selected_mode));
#endif
    // --- END Main menu ----

    // ---- SELECTED GAME MODE SHOULD BE LOADED HERE ----
    //
    //

    // ----- TEST CODE -----
    sf::View view;
    tf::character player1(window, view);
    tf::level::map_graphics level1("FiringRange.tmx", window);
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
    sf::Event event;

    while (window.isOpen())
    {
        window.clear(sf::Color::Black);
        window.setView(view);
        //Cursor position calculation
        sf::Vector2i position = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(position);
        cursor.setPosition(worldPos);
        // Draw objects
        level1.draw();
        player1.draw();
        player1.lookAtMouse();
        for (auto & action : Actions){
            action();
        }
        window.draw(cursor);
        window.display();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
    // ---- END TEST CODE -----
    TF_INFO("Terminating application!");
    return 0;
}