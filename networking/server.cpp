//
// Created by ramon on 19-1-2019.
//

#include "server.hpp"



server::server(unsigned short serverPort)
{
    socket.bind(serverPort);
    socket.setBlocking(1);
    NETWORK_INFO("port binded");

}


sf::Socket::Status server::serverReceive()
{

    if (socket.receive(rawPacket, lastIp, lastPort) != sf::Socket::Done) {
        NETWORK_INFO("received nothing");
        return sf::Socket::NotReady;
    }
    NETWORK_INFO("Received data");
    clientIps.insert(lastIp);
    return sf::Socket::Done; 
}

sf::Socket::Status server::serverSend() {
    NETWORK_INFO("Server send function");
    std::for_each(clientIps.begin(), clientIps.end(), [&](sf::IpAddress client){
        if (client != lastIp) {
            if (socket.send(rawPacket, client, lastPort) != sf::Socket::Done) {
                NETWORK_ERROR("Sending failed");
                return sf::Socket::Error;
            }
        }
    });
    return sf::Socket::Done;
}

void server::run() {
    NETWORK_INFO("Server running");
    while (true) {
        serverReceive();
        serverSend();
    }
}
