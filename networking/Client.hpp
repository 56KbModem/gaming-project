//
// Created by ramon on 19-1-2019.
//

#ifndef TOPFORCE_CLIENT1_HPP
#define TOPFORCE_CLIENT1_HPP
#include "../Topforce.hpp"
//#include <iostream>

namespace tf { namespace network{
    const unsigned short port = 53000;
class Client {
    sf::IpAddress serverIp;
    unsigned short serverPort;
    sf::UdpSocket socket;
    tf::PlayerPacket lastReceived;
    tf::TimePacket timeReceived;
    tf::DamagePacket lastDamagePacket;
    std::thread thread;
public:
    Client(sf::IpAddress &serverIp );
    sf::Socket::Status receive();
    sf::Socket::Status send(const tf::PlayerPacket &packet);
    sf::Socket::Status send(const tf::DamagePacket &packet);
    tf::PlayerPacket getLastPacket();
    tf::TimePacket getTime();
    tf::DamagePacket getDamage();

};
}}



#endif //TOPFORCE_CLIENT1_HPP
