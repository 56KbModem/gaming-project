// This is the server main file, it will
// be a dedicated server and must be
// compiled as a seperate executable!
#include "topForceServer.hpp"
#include "../topforce.hpp"

int main(){
    TF_INFO("Starting Topforce server!");
    std::cout << "HELLO!!!\n";

    bool server_is_running = true;
    uint16_t server_port = 31337;
    topforce_server current_server(server_port); // run server on port 31337

    while(server_is_running){
        current_server.listen();
        sf::sleep(sf::milliseconds(200));
        if (strncmp("STOP", current_server.get_data(), 4)){
            server_is_running = false;
        }
    }

    TF_INFO("Topforce server shutting down!...");
    return 0;
}
