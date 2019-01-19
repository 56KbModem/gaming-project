//
// Created by ramon on 19-1-2019.
//

#include "server.hpp"



server::server(unsigned short serverPort)
{
    socket.bind(serverPort);

}


sf::Socket::Status server::serverReceive()
{
    if (socket.receive(rawPacket, lastIp, lastPort) != sf::Socket::Done) {
        return sf::Socket::NotReady;
    }
    clientIps.insert(lastIp);
}

sf::Socket::Status server::serverSend() {

    std::for_each(clientIps.begin(), clientIps.end(), [&](sf::IpAddress client){
        if (client != lastIp) {
            if (socket.send(rawPacket, client, lastPort) != sf::Socket::Done) {
                return sf::Socket::Error;
            }
        }
    });
    return sf::Socket::Done;
}

void server::run() {
    while (true) {
        serverReceive();
        serverSend();
    }
}
