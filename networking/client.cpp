//
// Created by ramon on 19-1-2019.
//

#include "Client.hpp"

namespace tf {namespace network{
Client::Client(const unsigned short &myPort, sf::IpAddress &serverIp, const unsigned short &serverPort):
        myPort(myPort),
        serverIp(serverIp),
        serverPort(serverPort)
{
    socket.bind(myPort);
    socket.setBlocking(0);
    NETWORK_INFO("Client created");
}


sf::Socket::Status Client::receive() {
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
            rawPacket >>lastReceived.playerName >> lastReceived.position.x >> lastReceived.position.y >> lastReceived.rotation >> lastReceived.walking >> lastReceived.firing >>lastReceived.PlayerId;
           // std::cout<<"Player: ", lastReceived.playerName, "pos: ",lastReceived.position.x ,lastReceived.position.y <<"/n";
           return sf::Socket::Done;
        }
        else if( lastReceived.header == "time"){
            rawPacket >> timeReceived.minutes >> timeReceived.seconds;
            return sf::Socket::Done;
        }
    }

   // NETWORK_INFO("No package received");
    return sf::Socket::Error;

}

sf::Socket::Status Client::send(const tf::playerPacket &packet) {
    sf::Packet rawPacket;
    NETWORK_INFO("Sending: {} {}", packet.position.x, packet.position.y);
    if (rawPacket << "player" << packet.playerName <<packet.position.x << packet.position.y << packet.rotation << packet.walking << packet.firing <<packet.PlayerId) {

        NETWORK_INFO("Packet build succesfully");
        return (socket.send(rawPacket, serverIp, serverPort));
    }
    else {
        NETWORK_ERROR("Failed to build packet");
        return sf::Socket::Error;
    }
}

tf::playerPacket Client::getLastPacket() {
    return lastReceived;
}  
}}