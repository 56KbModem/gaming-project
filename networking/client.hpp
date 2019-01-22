//
// Created by ramon on 19-1-2019.
//

#ifndef TOPFORCE_CLIENT1_HPP
#define TOPFORCE_CLIENT1_HPP
#include "../topforce.hpp"
//#include <iostream>

namespace tf { namespace network{
class Client
{
    const unsigned short myPort;
    sf::IpAddress serverIp;
    unsigned short serverPort;
    sf::UdpSocket socket;
    tf::playerPacket lastReceived;
    tf::timePacket timeReceived;
    std::thread thread;


public:
    Client(const unsigned short &myPort,sf::IpAddress &serverIp, const unsigned short &serverPort );
    sf::Socket::Status receive();
    sf::Socket::Status send(const tf::playerPacket &packet);
    tf::playerPacket getLastPacket();
   // void threadReceive();
};
}}



#endif //TOPFORCE_CLIENT1_HPP
