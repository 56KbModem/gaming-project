//
// Created by ramon on 17-1-2019.
//
#include "Network_Client.hpp"
network_client::network_client(){}


network_client::bind(const int &port){
    if(new_socket.bind(port) != sf::Socket::Done){
        NETWORK_ERROR("Failed to bind port");
    }
}
uint8_t network_client::get_ip(){
    return client_ip;
}
uint8_t network_client::get_port(){
    return client_port;
}

void network_client::send(tf::network_packet &raw_package){
    sf::Packet raw_package;
    raw_package << packet.ip_sender << packet.x <<packet.y <<packet.rotation <<packet.firing <<packet.nickname;
    if (socket.send(raw_package)){
        NETWORK_INFO("package send");
    }
}

tf::network_packet network_client::received(){
   sf::Packet raw_packet;
   sock.receive(raw_packet);
   tf::network_packet packet;
   if( raw_packet >> packet.ip_sender >> packet.x >>packet.y >>packet.rotation >>packet.firing >>packet.nickname ){
       NETWORK_INFO("Received package");
       return packet;
   }
   else{
       NETWORK_INFO("No package received");
   }

}
