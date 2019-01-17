#include "topForceServer.hpp"

namespace tf{
    void topforce_server::connect_client() {
        sf::UdpSocket new_socket;
        if(new_socket.bind(my_portnumber) == sf::Socket::Done){
            players.push_back(new_socket);
            selector.add(new_socket);
        }
    }

    sf::IpAddress topforce_server::recv() {
        if (selector.wait(sf::seconds(10.f))){
            for (auto &player : players){
                if (selector.isReady(player)){
                    if (player.receive(data_buffer, 2, received, remote_host, remote_port) == sf::Socket::Done) {
                        for (auto &other_players : players){
                            if (other_players != player){
                                player
                            }
                        }
                    }
                    else{
                        NETWORK_WARN("Cannot receive data on socket!");
                    }
                    if (received > 1500) {
                        NETWORK_ERROR("Size of packet too big: {} bytes", received);
                    }
                }
            }
        }
    }

    void topforce_server::send(char *message,){
        for (sf::IpAddress player : players) {
            if (my_socket.send(message, 3, player, remote_port) != sf::Socket::Done) {
                NETWORK_WARN("Something went wrong while sending data: {}", message);
            }
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