//
// Created by nick on 2019-01-15.
//

#ifndef TOPFORCE_TOPFORCESERVER_HPP
#define TOPFORCE_TOPFORCESERVER_HPP

#include "../topforce.hpp"

class topforce_server {
private:
    char data_buffer[128]; // 1500 byte buffer
    std::size_t received;       // how many bytes have we received?

    uint16_t my_portnumber;
    sf::UdpSocket my_socket;

    sf::IpAddress remote_address;
    uint16_t remote_port;


public:
    topforce_server(uint16_t &portnumber):
        my_portnumber(portnumber)
    {
        if (my_socket.bind(my_portnumber) != sf::Socket::Done){
            TF_ERROR("Could not bind server to port: {}", my_portnumber);
        }
        else{
            TF_INFO("Game Server bound to port: {}", my_portnumber);
        }
    }

    void listen();
    char * get_data();

};


#endif //TOPFORCE_TOPFORCESERVER_HPP