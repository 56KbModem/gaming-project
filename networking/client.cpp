//
// Created by ramon on 15-1-2019.
//
#include "client.hpp"

clientConnect::clientConnect(sf::IpAddress ip, unsigned short port):
    ip(ip),
    port(port)
    {
        if (socket.bind(port) != sf::Socket::Done){
            TF_WARN("Failed to connect to server");
        }
    }

void clientConnect::send(char *message){
    if (socket.send(message,100,ip,port)!=sf::Socket::Done){
        TF_WARN("Sending failed");
    }
}

char* clientConnect::receive(){
    if (socket.receive(receive_buffer,100, received_size, ip, port)!= sf::Socket::Done){
        TF_WARN("Failed to receive data from server");
    }
    else {
        return receive_buffer;
    }
}

char* clientConnect::getBuffer() {
    return receive_buffer;
}