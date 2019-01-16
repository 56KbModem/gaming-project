//
// Created by ramon on 15-1-2019.
//
#include "client.hpp"

clientConnect::clientConnect(sf::IpAddress ip, const unsigned short &port):
    recipient(ip),
    port(port)
    {
        if (socket.bind(port) != sf::Socket::Done){
            TF_WARN("Failt to connect to server");
        }
    }

void clientConnect::send(char &message[100]){
    if (socket.send(message,100,ip,port)!=sf::Socket::Done){
        TF_WARN("Sending failt");
    }
}