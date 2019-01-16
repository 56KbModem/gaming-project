#include "topForceServer.hpp"


void topforce_server::listen() {
    if (my_socket.receive(data_buffer, 100, received, remote_address, remote_port) != sf::Socket::Done){
        TF_WARN("Cannot receive data on socket!");
    }

    TF_INFO("Data received: {}", data_buffer);
    TF_INFO("Remote host: {}:{}", remote_address, remote_port);
}

char * topforce_server::get_data(){
    return data_buffer;
}