//
// Created by ramon on 17-1-2019.
//

#ifndef TOPFORCE_NETWERK_CLIENT_HPP
#define TOPFORCE_NETWERK_CLIENT_HPP
#include "../topforce.hpp"

namespace tf {
    class network_client {
    private:
        sf::UdpSocket sock;
        sf::IpAddress client_ip;
        uint18_t client_port;
        std::size_t received;
        char *data_buffer[1500];
    public:
        network_client();
        bind(const int &port);
        uint8_t get_ip();
        uint8_t get_port();
        void send(tf::network_packet &packet);
        tf::network_packet received();
        tf::network_packet get_buf();





    };
}
#endif //TOPFORCE_NETWERK_CLIENT_HPP
