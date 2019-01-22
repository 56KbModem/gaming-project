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
      //  NETWORK_INFO("IN While");
       // sf::sleep(sf::milliseconds(1000));
        sf::Packet rawPacket;
        sf::IpAddress tmpIp;
        unsigned short tmpPort;
        if (socket.receive(rawPacket, tmpIp, tmpPort) != sf::Socket::Done) {
           //return sf::Socket::NotReady;
        }
        if (rawPacket >> lastReceived.header) {
            //data extraxted
#if DEBUG
            NETWORK_INFO("packet extracted succesfully");
#endif

            if (lastReceived.header == "player") {
                rawPacket >> lastReceived.playerName >> lastReceived.position.x >> lastReceived.position.y
                          >> lastReceived.rotation >> lastReceived.walking >> lastReceived.firing
                          >> lastReceived.PlayerId;
                // std::cout<<"Player: ", lastReceived.playerName, "pos: ",lastReceived.position.x ,lastReceived.position.y <<"/n";
               // return sf::Socket::Done;
            } else if (lastReceived.header == "time") {
                rawPacket >> timeReceived.minutes >> timeReceived.seconds;
                //return sf::Socket::Done;
            }
        }

        // NETWORK_INFO("No package received");
       // return sf::Socket::Error;
    }
}

sf::Socket::Status Client::send(const tf::playerPacket &packet) {
    sf::Packet rawPacket;
#if DEBUG
   // NETWORK_INFO("Sending: {} {}", packet.position.x, packet.position.y);
#endif
    if (rawPacket << "player" << packet.playerName <<packet.position.x << packet.position.y << packet.rotation << packet.walking << packet.firing <<packet.PlayerId) {
#if DEBUG
     //   NETWORK_INFO("Packet build succesfully");
#endif
        return (socket.send(rawPacket, serverIp, serverPort));
    }
    else {
      //  NETWORK_ERROR("Failed to build packet");
        return sf::Socket::Error;
    }
}

tf::playerPacket Client::getLastPacket() {
    return lastReceived;
}  
}}