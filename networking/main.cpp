// This is the server main file, it will
// be a dedicated server and must be
// compiled as a seperate executable!
#include "topForceServer.hpp"

int main(){
    tf::log::init();
    TF_INFO("Starting Topforce server!");

    //bool server_is_running = true;
    uint16_t server_port = 31337;
    tf::topforce_server current_server(server_port); // run server on port 31337

    for (int i=0; i < 4; ++i) {
        current_server.connect_client();
    }
    while(1){
        current_server.run_server();
        std::cout << "received: " << current_server.get_data() << "\nsize: " << current_server << '\n';
        if (std::string(current_server.get_data()) == "HELLO"){
            current_server.send("HELLO BACK");
        }
        else{
            current_server.send("ABC");
        }

    }

    TF_INFO("Topforce server shutting down!...");
    return 0;
}
