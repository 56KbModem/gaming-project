#include "topForceServer.hpp"
#include "Network_Client.hpp"

namespace tf{
    void topforce_server::connect_client() {
        network_client client;
        //sf::UdpSocket new_socket;
        if(client.bind(my_portnumber) == sf::Socket::Done){
            players.push_back(client);
            selector.add(client);
        }
    }

    sf::IpAddress topforce_server::recv() {
        if (selector.wait(sf::seconds(10.f))){
            for (auto &player : players){
                if (selector.isReady(player)){
                    if (player.receive() == sf::Socket::Done) {
                        for (auto &other_player : players){
                            if (other_player != player){
                                other_player.send(player.get_buf());
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