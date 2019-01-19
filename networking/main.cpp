// This is the server main file, it will
// be a dedicated server and must be
// compiled as a seperate executable!
//#include "topForceServer.hpp"
#include "server1.hpp"
int main(){
    auto my_server=server(13337);
    TF_INFO("Server created");
    my_server.run();
    TF_INFO("Topforce server shutting down!...");
    return 0;
}
