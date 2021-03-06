// This is the Server main file, it will
// be a dedicated Server and must be
// compiled as a seperate executable!

#include "server.hpp"
int main(int argc, char ** argv){
    // Setup logger
    tf::Log::init();
    const unsigned short gamePort = 53000;

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

    int minutes;
    int seconds;
    if (iss_1 >> minutes && iss_2 >> seconds){ // test if conversion happened
        NETWORK_INFO("Command line parsed correctly");
    }
    else {
        NETWORK_ERROR("Cannot parse arguments : {}  {}", argv[1], argv[2]);
        return 1; // give error status to the shell
    }


    NETWORK_INFO("Starting main");
    Server my_server(gamePort, minutes, seconds);
    TF_INFO("Server created");
    my_server.run();
    TF_INFO("Topforce Server shutting down!...");
    return 0;
}
