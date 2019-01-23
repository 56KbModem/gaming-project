//
// Created by ramon on 19-1-2019.
//

#include "Client.hpp"

namespace tf {namespace network{
Client::Client(const unsigned short &myPort, sf::IpAddress &serverIp, const unsigned short &serverPort):
        myPort(myPort),
        serverIp(serverIp),
        serverPort(serverPort),
        thread(&tf::network::Client::receive, this)

{
    socket.bind(myPort);
    socket.setBlocking(0);
    thread.detach();
    NETWORK_INFO("Client created");
}

sf::Socket::Status Client::receive() {
    while(true) {
        sf::Packet rawPacket;
        sf::IpAddress tmpIp;
        unsigned short tmpPort;
        if (socket.receive(rawPacket, tmpIp, tmpPort) != sf::Socket::Done) {
        }
        if (rawPacket >> lastReceived.header) {
            if (lastReceived.header == "player") {
                rawPacket >> lastReceived.playerName >> lastReceived.position.x >> lastReceived.position.y
                          >> lastReceived.rotation >> lastReceived.walking >> lastReceived.firing
                          >> lastReceived.PlayerId;
            } else if (lastReceived.header == "time") {
                rawPacket >> timeReceived.minutes >> timeReceived.seconds;
            }
        }
    }

}

sf::Socket::Status Client::send(const tf::PlayerPacket &packet) {
    sf::Packet rawPacket;
    if (rawPacket << "player" << packet.playerName <<packet.position.x << packet.position.y << packet.rotation << packet.walking << packet.firing <<packet.PlayerId) {

        return (socket.send(rawPacket, serverIp, serverPort));
    }
    else {
        return sf::Socket::Error;
    }
}

tf::PlayerPacket Client::getLastPacket() {
    return lastReceived;
}  
}}