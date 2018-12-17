#include "Headers.hpp"

int main( int argc, char *argv[] ){

    auto console = spdlog::stdout_color_mt("Console");
    auto err_logger = spdlog::stderr_color_mt("stderr");
    console->info("Welcome to spdlog!");
    err_logger->error("This is an error test with arg: {}","Hello");

    // Anti aliasing
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    // Window object
    sf::RenderWindow window( sf::VideoMode(1280, 720), "Topforce", sf::Style::Titlebar | sf::Style::Close, settings);

    while (window.isOpen()) {
        window.clear();
        // Draw items

        window.display();

        sf::sleep( sf::milliseconds( 20 ));

        sf::Event event;
        while( window.pollEvent(event) ){
            if( event.type == sf::Event::Closed ){
                window.close();
            }
        }
    }
    std::cout << "Terminating application!\n";
    return 0;
}