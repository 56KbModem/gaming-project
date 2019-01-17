#include "topforce.hpp"
#include "gui/main_menu.hpp"
#include "character/character.hpp"
#include "level/map_graphics.hpp"

int main(){
    // Setup logger
    tf::log::init();
    TF_WARN("Initialized log!");

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

    tf::game_modes selected_mode;

    tf::gui::main_menu menu(window);
    selected_mode = menu.run();
    TF_INFO("Chosen game mode: {}",int(selected_mode));
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
                        action([&](){return currentPosition == player1.getPosition();}, [&](){player1.setTexture("STATIONARY");})
    };
    sf::Event event;
    while (window.isOpen())
    {
        window.clear(sf::Color::Black);
        window.setView(view);
        level1.draw();
        player1.draw();
        player1.lookAtMouse();
        for (auto & action : Actions){
            action();
        }
        window.display();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
    TF_INFO("Terminating application!");
    return 0;
}