//
// Created by ramon on 15-1-2019.
//
#include "client.hpp"

clientConnect::clientConnect(std::string &ip, int port) {
    status = socket.connect(ip,port);
    if (status != sf::Socket::Done){
        TF_ERROR("Client connection to server fail.");
    }
}

std::string clientConnect::GetRemoteIp() {
    return socket.getRemoteAddress();
}

std::String clientConnect::getRemotePort(){
    return socket.getRemotePort();
}

void clientConnect::send(char &message[100]){
    if (socket.send(message,100) != sf::socket::Done){
        TF_WARN("Failt to send data to server");
    }
}