//
// Created by ramon on 19-1-2019.
//

#include "client.hpp"

client::client(const unsigned short &myPort, sf::IpAddress &serverIp, const unsigned short &serverPort):
        myPort(myPort),
        serverIp(serverIp),
        serverPort(serverPort)
{
    socket.bind(myPort);
    NETWORK_INFO("Client created");
}


sf::Socket::Status client::receive() {
    sf::Packet rawPacket;
    sf::IpAddress tmpIp;
    unsigned short tmpPort;
    if (socket.receive(rawPacket,tmpIp,tmpPort)!=sf::Socket::Done){
        return sf::Socket::NotReady;
    }
    if (rawPacket >> lastReceived.header) {
        //data extraxted
        NETWORK_INFO("packet extracted succesfully");

        if (lastReceived.header == "player"){
            rawPacket >> lastReceived.position.x >> lastReceived.position.y >> lastReceived.rotation >> lastReceived.walking >> lastReceived.firing;
        }
        else if( lastReceived.header == "time"){
            rawPacket >> timeReceived.minutes >> timeReceived.seconds;
        }
    }

    NETWORK_INFO("No package received");
    return sf::Socket::Error;

}

sf::Socket::Status client::send(const tf::playerPacket &packet) {
    sf::Packet rawPacket;
    if (rawPacket << "player" << packet.position.x << packet.position.y << packet.rotation << packet.walking << packet.firing) {

        NETWORK_INFO("Packet build succesfully");
        return (socket.send(rawPacket, serverIp, serverPort));
    }
    else {
        NETWORK_ERROR("Failed to build packet");
        return sf::Socket::Error;
    }
}

tf::network_packet client::getLastPacket() {
    return lastReceived;
}