//
// Created by ramon on 17-1-2019.
//
#include "Network_Client.hpp"

network_client::network_client(const int &port){
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

void network_client::send(tf::network_packet &packet){
    if (socket.send(packet ,52,client_ip,client_port)!=sf::Socket::Done){
        NETWORK_ERROR("Failed to send packet");
    }
}

tf::network_packet network_client::received(){
    if (sock.receive(data_buffer, 52, received, client_ip, client_port) == sf::Socket::Done){
        return data_buffer;
    }
    else{
        NETWORK_ERROR("Error receiving packet");
    }
}