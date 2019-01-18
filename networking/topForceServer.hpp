//
// Created by nick on 2019-01-15.
//

#ifndef TOPFORCE_TOPFORCESERVER_HPP
#define TOPFORCE_TOPFORCESERVER_HPP

#include "../topforce.hpp"
#include "Network_Client.hpp"

namespace tf{
    class topforce_server {
    private:
        uint16_t my_portnumber;     // port on which to bind the server
        sf::SocketSelector selector;

        std::vector<tf::network_client> players; // stores socket for players
    public:
        topforce_server(uint16_t &portnumber):
                my_portnumber(portnumber)
        {}

        void connect_client();
        void run_server();
        tf::network_packet get_data();
    };
}



#endif //TOPFORCE_TOPFORCESERVER_HPP