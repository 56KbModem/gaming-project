#include "topforce.hpp"
#include "gui/main_menu.hpp"
#include "level/MapGraphics.hpp"

int main(){
    // Setup logger
    tf::log::init();
    TF_WARN("Initialized log!");

    // Anti aliasing
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // Window object
    sf::Image window_icon;
    window_icon.loadFromFile("assets/images/Topforce_icon.png");
    sf::RenderWindow window( sf::VideoMode(1920, 1080), "Topforce",sf::Style::Titlebar | sf::Style::Close, settings);
    window.setIcon(512, 512, window_icon.getPixelsPtr());

    tf::game_modes selected_mode;

    tf::gui::main_menu menu(window);
    selected_mode = menu.run();
    TF_INFO("Chosen game mode: {}",int(selected_mode));

    tf::level::MapGraphics level1("FiringRange.tmx", window);
    
    while (window.isOpen())
    {
        window.clear(sf::Color::Black);
        level1.draw();
        window.display();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
    TF_INFO("Terminating application!");
    return 0;
}