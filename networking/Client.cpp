//
// Created by ramon on 19-1-2019.
//

#include "Client.hpp"

namespace tf {namespace network{
Client::Client(sf::IpAddress &serverIp):

        serverIp(serverIp),
        serverPort(port),
        thread(&tf::network::Client::receive, this)

{
    socket.bind(port);
    socket.setBlocking(0);
    thread.detach();
    NETWORK_INFO("Client created");
}

Client::~Client() {
    socket.unbind();
    stopThread = true;
}

void Client::receive() {
    while(!stopThread) {
        sf::Packet rawPacket;
        sf::IpAddress tmpIp;
        std::string header;
        unsigned short tmpPort;
        if (socket.receive(rawPacket, tmpIp, tmpPort) != sf::Socket::Done) {
        }
        if (rawPacket >> header) {
            if (header == "player") {
                rawPacket >> lastReceived.playerName >> lastReceived.position.x >> lastReceived.position.y
                          >> lastReceived.rotation >> lastReceived.walking >> lastReceived.firing
                          >> lastReceived.PlayerId >> lastReceived.firePos.x >>lastReceived.firePos.y;
                lastReceived.header=header;
            }
            else if (header == "time") {
                rawPacket >> timeReceived.minutes >> timeReceived.seconds;
                timeReceived.header=header;
            }
            else if (header=="damage"){
                lastDamagePacket.header=header;
                rawPacket >> lastDamagePacket.died >> lastDamagePacket.hitById >> lastDamagePacket.playerId >>lastDamagePacket.damage;
            }
            else if(header=="leave"){
                lastLeaved = tmpIp ;
            }
        }
        sf::sleep(sf::milliseconds(5));
    }

}

sf::Socket::Status Client::send(const tf::PlayerPacket &packet) {
    sf::Packet rawPacket;
    if (rawPacket << "player" << packet.playerName <<packet.position.x << packet.position.y << packet.rotation << packet.walking
    << packet.firing <<packet.PlayerId << packet.firePos.x <<packet.firePos.y) {

        return (socket.send(rawPacket, serverIp, serverPort));
    }
    else {
        return sf::Socket::Error;
    }
}

sf::Socket::Status Client::send(const tf::DamagePacket &packet){
    sf::Packet rawPacket;
    if (rawPacket << "damage" << packet.died << packet.hitById <<packet.playerId << packet.damage) {

        return (socket.send(rawPacket, serverIp, serverPort));
    }
    else {
        return sf::Socket::Error;
    }
}

tf::PlayerPacket Client::getLastPacket() {
    return lastReceived;
}

tf::TimePacket Client::getTime(){
    return timeReceived ;
}

tf::DamagePacket Client::getDamage(){
    if (lastDamagePacket.header=="damage" && lastDamagePacket.playerId == sf::IpAddress::getLocalAddress().toInteger()){
        tf::DamagePacket tmp= lastDamagePacket;
        lastDamagePacket.header="readed";
        return tmp;
    }
    return {"damage",0,0,0}; 
}

sf::IpAddress Client::getLastLeaved(){
    sf::IpAddress tmp = lastLeaved;
    lastLeaved = "";
    return tmp;
}
}}