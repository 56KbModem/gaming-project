#include "topforce.hpp"
#include "gui/main_menu.hpp"
#include "level/map_loader.hpp"
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

    tf::level::map_loader level1("FiringRange.tmx");
    
    while (window.isOpen())
    {
        window.clear(sf::Color::Black);
        level1.draw(window);
        window.display();
    }
    TF_INFO("Terminating application!");
    return 0;
}