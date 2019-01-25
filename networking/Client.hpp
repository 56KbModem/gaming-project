//
// Created by ramon on 19-1-2019.
//

#ifndef TOPFORCE_CLIENT1_HPP
#define TOPFORCE_CLIENT1_HPP
#include "../Topforce.hpp"
//#include <iostream>

namespace tf { namespace network{
class Client {
    sf::IpAddress serverIp;
    unsigned short serverPort;
    sf::UdpSocket socket;
    tf::PlayerPacket lastReceived;
    tf::TimePacket timeReceived;
    std::thread thread;
public:
    Client(const unsigned short &myPort,sf::IpAddress &serverIp, const unsigned short &serverPort );
    sf::Socket::Status receive();
    sf::Socket::Status send(const tf::PlayerPacket &packet);
    tf::PlayerPacket getLastPacket();
    tf::TimePacket getTime();
};
}}



#endif //TOPFORCE_CLIENT1_HPP
