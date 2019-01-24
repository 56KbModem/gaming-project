// This is the server main file, it will
// be a dedicated server and must be
// compiled as a seperate executable!

#include "Server.hpp"
int main(int argc, char ** argv){
    // Setup logger
    tf::Log::init();
#if DEBUG
    TF_WARN("TopForce logger initialized!");
    NETWORK_WARN("Network logger initialized!");
#endif

    /* parsing command-line arguments */
    if (argc < 3){
        std::cerr << "Missing arguments:\n";
        std::cerr << "Usage: " << argv[0]
        << " <minutes>" << " <seconds>" << '\n'; // we push this to stderr, not the logger
        return 1; // give error status to the shell
    }

    /* convert arguments to integers */
    std::istringstream iss_1(argv[1]);
    std::istringstream iss_2(argv[2]);

    int minute;
    int second;
    if (iss_1 >> minute && iss_2 >> second){ // test if conversion happened
        NETWORK_INFO("Command line parsed correctly");
    }
    else {
        NETWORK_ERROR("Cannot parse arguments : {}  {}", argv[1], argv[2]);
        return 1; // give error status to the shell
    }



    NETWORK_INFO("Starting main");
    Server my_server(53000, minute, second);
    TF_INFO("Server created");
    my_server.run();
    TF_INFO("Topforce server shutting down!...");
    return 0;
}
