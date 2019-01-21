//
// Created by ramon on 19-1-2019.
//

#ifndef TOPFORCE_CLIENT1_HPP
#define TOPFORCE_CLIENT1_HPP
#include "../topforce.hpp"
//#include <iostream>
class client
{
    const unsigned short myPort;
    sf::IpAddress serverIp;
    unsigned short serverPort;
    sf::UdpSocket socket;
    tf::network_packet lastReceived;


public:
    client(const unsigned short &myPort,sf::IpAddress &serverIp, const unsigned short &serverPort );
    sf::Socket::Status receive();
    sf::Socket::Status send(const tf::network_packet &packet);
    tf::network_packet getLastPacket();
};


#endif //TOPFORCE_CLIENT1_HPP
