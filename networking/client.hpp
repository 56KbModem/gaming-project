//
// Created by ramon on 15-1-2019.
//

#ifndef TOPFORCE_CLIENT_HPP
#define TOPFORCE_CLIENT_HPP
#include "../topforce.hpp"
#include <fstream>
#include <algorithm>
#include <string>
#include <stdlib.h>

class clientConnect{
private:
    std::array<char,15> my_ip;
    sf::IpAddress server_ip;
    unsigned short port;
    sf::UdpSocket socket;
    tf::network_packet receivedPacket;
public:
    clientConnect(sf::IpAddress ip, unsigned short port);
    void send(tf::network_packet packet);
    void receive();

};


#endif //TOPFORCE_CLIENT_HPP
