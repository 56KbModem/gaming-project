//
// Created by ramon on 17-1-2019.
//
#include "Network_Client.hpp"

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

void network_client::send(tf::network_packet packet){
    sf::Packet raw_packet
    raw_package << packet.ip_sender << packet.x <<packet.y <<packet.rotation <<packet.firing <<packet.nickname;
    if (socket.send(raw_package)){
        NETWORK_INFO("package send");
    }
}

sf::Socket::status network_client::received(){
   sock.receive(raw_packet);
   tf::network_packet packet;
   if( raw_packet >> packet.ip_sender >> packet.x >>packet.y >>packet.rotation >>packet.firing >>packet.nickname ){
       NETWORK_INFO("Received package");
       current_data=packet;
      return sf::Socket::Done;
   }
   else{
       NETWORK_INFO("No package received");
       return sf::Socket::Error;
   }

}

 get_data(){
    return current_data;
}