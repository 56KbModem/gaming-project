//
// Created by ramon on 19-1-2019.
//

#ifndef TOPFORCE_SERVER1_HPP
#define TOPFORCE_SERVER1_HPP


#include <set>
#include <algorithm>
#include "../topforce.hpp"


class Server
{
    sf::UdpSocket socket;
    std::set<sf::IpAddress> clientIps;
    sf::Packet playerPacket;
    sf::Packet timePacket;
    sf::IpAddress lastIp;
    unsigned short lastPort;

    sf::Clock timerClock;

    int minuteToPlay;
    int secondToPlay;

public:
    Server(unsigned short ServerPort, int minuteToPlay, int secondToPlay);
    sf::Socket::Status ServerReceive();
    sf::Socket::Status playerSend();
    sf::Socket::Status timeSend();
    void run();

};
#endif //TOPFORCE_SERVER1_HPP
