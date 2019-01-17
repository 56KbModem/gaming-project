#include "topForceServer.hpp"

namespace tf{
    void topforce_server::listen() {
        if (my_socket.receive(data_buffer, 100, received, remote_address, remote_port) != sf::Socket::Done){
            TF_WARN("Cannot receive data on socket!");
        }

        if (received > 1500){
            TF_ERROR("Size of packet too big: {} bytes", received);
        }

    }

    void topforce_server::send(char *message){
        if (my_socket.send(message, 100, remote_address, remote_port) != sf::Socket::Done){
            TF_WARN("Something went wrong while sending data: {}", message);
        }
    }

    char * topforce_server::get_data(){
        return data_buffer;
    }

    std::size_t topforce_server::get_data_size() {
        return received;
    }

    std::string topforce_server::get_client_params(){
        return remote_address.toString() + ": " + std::to_string(remote_port);
    }
}