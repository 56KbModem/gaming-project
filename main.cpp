#include "topforce.hpp"
#include "gui/main_menu.hpp"
#include "character/character.hpp"
#include "level/map_graphics.hpp"
#include "abstracts/screen_object.hpp"
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
    tf::character player1(window);
    tf::level::map_graphics firing_range("FiringRange.tmx", window);
    
    sf::View view;
    view.setSize(1920.f, 1080.f);

    while (window.isOpen())
    {
        window.clear(sf::Color::Black);
        window.setView(view);
        //Cursor position calculation
        sf::Vector2i position = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(position);
        cursor.setPosition(worldPos);
        // Draw objects
        firing_range.draw();
        player1.move(view);
        player1.draw();
        window.draw(cursor);
        window.display();
        if (firing_range.intersects(player1)) {
            TF_INFO("collision detected");
        }
        sf::Event event;
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