//
// Created by ramon on 19-1-2019.
//

#ifndef TOPFORCE_SERVER1_HPP
#define TOPFORCE_SERVER1_HPP

#include <iostream>
#include <set>
#include <algorithm>
#include "../topforce.hpp"


class server
{
    sf::UdpSocket socket;
    std::set<sf::IpAddress> clientIps;
    sf::Packet rawPacket;
    sf::IpAddress lastIp;
    unsigned short lastPort;

public:
    server(unsigned short serverPort);
    sf::Socket::Status serverReceive();
    sf::Socket::Status serverSend();
    void run();

};
#endif //TOPFORCE_SERVER1_HPP
