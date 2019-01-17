//
// Created by ramon on 16-1-2019.
//
#include "client.hpp"


void main(){
    auto connection = clientConnect(sf::IpAddress("145.89.97.172"), 31337);
    while (true) {
       // auto connection = clientConnect(sf::IpAddress("145.89.97.172"), 31337);
        connection.send("hello world");
        sf::sleep(sf::seconds(1));
    }
}
