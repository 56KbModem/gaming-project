//
// Created by nick on 2019-01-15.
//

#ifndef TOPFORCE_TOPFORCESERVER_HPP
#define TOPFORCE_TOPFORCESERVER_HPP

#include "../topforce.hpp"
namespace tf{
    class topforce_server {
    private:
        char data_buffer[1500]; // 1500 byte buffer
        std::size_t received;       // how many bytes have we received?

        uint16_t my_portnumber;     // port on which to bind the server
        sf::SocketSelector selector;

        std::vector<sf::UdpSocket> players; // stores socket for players
        uint16_t remote_port;
        sf::IpAddress remote_host





    public:
        topforce_server(uint16_t &portnumber):
                my_portnumber(portnumber)
        {}

        void connect_client();
        void recv();
        void send(char *message);
        char * get_data();
        std::size_t get_data_size();
        std::string get_client_params();

    };
}



#endif //TOPFORCE_TOPFORCESERVER_HPP