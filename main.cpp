#include "Topforce.hpp"
#include "gui/MainMenu.hpp"
#include "gui/TopforceWindow.hpp"
#include "gamemodes/FreeForAll.hpp"
#include "SoundManager.hpp"

int main(){
    // Setup logger
    tf::Log::init();
#if DEBUG
    TF_WARN("TopForce logger initialized!");
    NETWORK_WARN("Network logger initialized!");
#endif

    tf::TopforceWindow window; // customized window
    window.setWindowIcon();
    window.setCursorIcon("crosshair.png");

    // ---- Main Menu ----
    tf::GameModes selectedMode;
    tf::gui::MainMenu menu(window);
    //sf::IpAddress ipAddress("wodan.wifi.hu.nl");
    //sf::IpAddress ipAddress("145.89.78.92");
    sf::IpAddress ipAddress("145.89.79.178");

    std::unique_ptr<tf::GameMode> gameMode;
    while (window.isOpen()) {
        selectedMode = menu.run();
        switch (selectedMode) {
            case tf::GameModes::Free_For_All: {
                gameMode = std::make_unique<tf::gamemode::FreeForAll>(window, "FiringRange.tmx", ipAddress);
                gameMode->run();
                break;
            }
            default:
                break;
        }
    }
    return 0;
}
