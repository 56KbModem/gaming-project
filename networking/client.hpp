//
// Created by ramon on 15-1-2019.
//

#ifndef TOPFORCE_CLIENT_HPP
#define TOPFORCE_CLIENT_HPP
#include "../topforce.hpp"

class clientConnect{
private:
    sf::TcpSocket socket;
    sf::Socket::Status status;
public:
    clientConnect(std::string &ip, int port);
    std::string GetRemoteIp();
    std::String getRemotePort();
    void send(char &message[100]);

};


#endif //TOPFORCE_CLIENT_HPP
