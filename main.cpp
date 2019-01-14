#include "topforce.hpp"
#include "gui/main_menu.hpp"

#include <tmxlite/Map.hpp>
#include "level/SFMLOrthogonalLayer.hpp"

int main(){
    // Setup logger
    tf::log::init();
    TF_WARN("Initialized log!");

    // Anti aliasing
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    // Window object
    sf::RenderWindow window( sf::VideoMode(1920, 1080), "Topforce",sf::Style::Titlebar | sf::Style::Close, settings);

    game_mode selected_mode;

    tf::gui::main_menu menu(window);
    selected_mode = menu.run();
    TF_INFO("Chosen game mode: {}",int(selected_mode));

    // Load level test
    tmx::Map map;
    map.load("assets/levels/level1.tmx");

    MapLayer layerZero(map, 0);
    MapLayer layerOne(map, 1);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(layerZero);
        window.draw(layerOne);
        window.display();
    }
    TF_INFO("Terminating application!");
    return 0;
}