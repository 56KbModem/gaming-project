#include "topforce.hpp"
#include "gui/main_menu.hpp"

int main(){
    // Setup loggers
    auto console = spdlog::stdout_color_mt("console");
    auto err_logger = spdlog::stderr_color_mt("stderr");
    // Anti aliasing
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    // Window object
    sf::RenderWindow window( sf::VideoMode(1920, 1080), "Topforce", sf::Style::Titlebar | sf::Style::Close, settings);

    game_mode selected_mode;

    tf::gui::main_menu menu(window);
    selected_mode = menu.run();

    console->info("Chosen game mode: {}",int(selected_mode));

    window.close();
    console->info("Terminating application!");
    return 0;
}