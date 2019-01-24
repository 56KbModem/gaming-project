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
    selectedMode = menu.run(); // selected_mode indicates which game mode needs to be called
    sf::IpAddress ipAddress("145.89.98.232");


#if DEBUG
    TF_INFO("Chosen game mode: {}", int(selectedMode));
#endif

    switch(selectedMode){
        case tf::GameModes::Free_For_All:{
            tf::gamemode::FreeForAll freeForAll(window,"FiringRange.tmx", ipAddress);
            freeForAll.run();
            break;
        }
        default:
            break;
    }
#if DEBUG
    TF_INFO("Terminating application!");
#endif
    return 0;
}