//
// Created by nick on 2019-01-15.
//

#ifndef TOPFORCE_TOPFORCESERVER_HPP
#define TOPFORCE_TOPFORCESERVER_HPP

#include <SFML/Network.hpp>
#include <cstdint>

class topForceServer {
private:
    uint8_t data_buffer[1500]; // 1500 byte buffer
    sf::TcpListener my_listener;
    std::vector<sf::TcpSocket, 8> clients;

public:
    

};


#endif //TOPFORCE_TOPFORCESERVER_HPP
