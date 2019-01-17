#include "topforce.hpp"
#include "gui/main_menu.hpp"
#include "networking/client.hpp"

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
    char mes[100]= "HELLO";
    TF_INFO("Chosen game mode: {}",int(selected_mode));
    window.close();
    auto connection = clientConnect(sf::IpAddress("145.89.97.172"), 31337);
    while (true) {
        connection.send(mes);
        TF_INFO("sending to nick");

        //connection.send(connection.receive());
        TF_INFO("received: ",connection.receive()," and sending back");
    }
    window.close();
    TF_INFO("Terminating application!");
    return 0;
}