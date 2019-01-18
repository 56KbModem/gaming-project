#include "topForceServer.hpp"
#include "Network_Client.hpp"
namespace tf{
    void topforce_server::connect_client() {
        network_client client;
        if(client.bind(my_portnumber) == sf::Socket::Done){
            players.push_back(client);
            selector.add(client);
        }
    }

    void topforce_server::run_server() {
        if (selector.wait(sf::seconds(10.f))){
            for (auto &player : players){
                if (selector.isReady(player)){
                    if (player.received() == sf::Socket::Done) {
                        for (auto &other_player : players) {
                            if (other_player.get_ip() != player.get_ip()) {
                                other_player.send(player.get_data());
                            }
                        }
                    }
                    else{
                        NETWORK_WARN("Cannot receive data on socket!");
                    }

                }
            }
        }
    }

}