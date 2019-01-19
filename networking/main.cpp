// This is the server main file, it will
// be a dedicated server and must be
// compiled as a seperate executable!

#include "server1.hpp"
int main(){
    // Setup logger
    tf::Log::init();
#if DEBUG
    TF_WARN("TopForce logger initialized!");
    NETWORK_WARN("Network logger initialized!");
#endif
    NETWORK_INFO("Starting main");
    server my_server(53000);
    TF_INFO("Server created");
    my_server.run();
    TF_INFO("Topforce server shutting down!...");
    return 0;
}
