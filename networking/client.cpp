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
    if (rawPacket >> lastReceived.x >> lastReceived.y >> lastReceived.rotation >> lastReceived.firing) {
        //data extraxted
        NETWORK_INFO("packet extracted succesfully");
        return sf::Socket::Done;
    }
    NETWORK_INFO("No package received");
    return sf::Socket::Error;

}

sf::Socket::Status client::send(const tf::network_packet &packet) {
    sf::Packet rawPacket;
    if (rawPacket << packet.x << packet.y << packet.rotation << packet.firing) {

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