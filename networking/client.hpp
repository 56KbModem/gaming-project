//
// Created by ramon on 15-1-2019.
//

#ifndef TOPFORCE_CLIENT_HPP
#define TOPFORCE_CLIENT_HPP
#include "../topforce.hpp"

class clientConnect{
private:
    sf::IpAddress ip;
    unsigned short port;
    sf::UdpSocket socket;
    char receive_buffer[1500];
    std::size_t received_size;
public:
    clientConnect(sf::IpAddress ip, unsigned short port);
    void send(char *message);
    char* receive();
    char* getBuffer();

};


#endif //TOPFORCE_CLIENT_HPP
