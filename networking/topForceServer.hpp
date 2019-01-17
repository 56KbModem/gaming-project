//
// Created by nick on 2019-01-15.
//

#ifndef TOPFORCE_TOPFORCESERVER_HPP
#define TOPFORCE_TOPFORCESERVER_HPP

#include "../topforce.hpp"
namespace tf{
    class topforce_server {
    private:
        char data_buffer[1500]; // 1500 byte buffer
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
                //TF_ERROR("Could not bind server to port: {}", my_portnumber);
            }
            else{
                //TF_INFO("Game Server bound to port: {}", my_portnumber);
            }
        }

        void recv();
        void send(char *message);
        char * get_data();
        std::size_t get_data_size();
        std::string get_client_params();

    };
}



#endif //TOPFORCE_TOPFORCESERVER_HPP