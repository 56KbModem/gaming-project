//
// Created by ramon on 17-1-2019.
//

#ifndef TOPFORCE_NETWERK_CLIENT_HPP
#define TOPFORCE_NETWERK_CLIENT_HPP
#include "../topforce.hpp"

namespace tf {
class network_client: public sf::socket {
    private:
        sf::IpAddress client_ip;
        uint18_t client_port;
        std::size_t received;
    public:
        network_client();
        uint8_t get_ip();
        uint8_t get_port();
        void send(tf::network_packet &packet);
        tf::network_packet received();
    };
}
#endif //TOPFORCE_NETWERK_CLIENT_HPP
