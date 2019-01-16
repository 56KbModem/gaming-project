//
// Created by ramon on 15-1-2019.
//

#ifndef TOPFORCE_CLIENT_HPP
#define TOPFORCE_CLIENT_HPP
#include "../topforce.hpp"

class clientConnect{
private:
    sf::IpAddress ip;
    unsigned short &port;
    sf::UdpSocket socket;
public:
    clientConnect(sf::IpAddress ip, const unsigned short &port);
    send(char &message[100]);

};


#endif //TOPFORCE_CLIENT_HPP
