//
// Created by ramon on 17-1-2019.
//

#ifndef TOPFORCE_NETWERK_CLIENT_HPP
#define TOPFORCE_NETWERK_CLIENT_HPP
#include "../topforce.hpp"

namespace tf {
class network_client: public sf::UdpSocket {
    private:
        tf::network_packet current_data;
    public:
        network_client();
        uint8_t get_ip();
        uint8_t get_port();
        void send(tf::network_packet packet);
        sf::Socket::Status received();
        tf::network_packet get_data();
    };
}
#endif //TOPFORCE_NETWERK_CLIENT_HPP
