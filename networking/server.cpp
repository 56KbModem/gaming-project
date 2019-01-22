#include "server.hpp"


server::server(unsigned short serverPort)
{
    socket.bind(serverPort);
    socket.setBlocking(1);
    NETWORK_INFO("port binded");

}


sf::Socket::Status server::serverReceive()
{

    if (socket.receive(rawPacket, lastIp, lastPort) != sf::Socket::Done) {
#if DEBUG
        NETWORK_INFO("received nothing");
#endif // DEBUG
        return sf::Socket::NotReady;
    }
#if DEBUG
    NETWORK_INFO("Received data");
#endif // DEBUG
    clientIps.insert(lastIp);
    return sf::Socket::Done; 
}

sf::Socket::Status server::playerSend() {
#if DEBUG
    NETWORK_INFO("Server send function");
#endif // DEBUG
    std::for_each(clientIps.begin(), clientIps.end(), [&](sf::IpAddress client){
        if (client != lastIp) {
            if (socket.send(rawPacket, client, lastPort) != sf::Socket::Done) {
                NETWORK_ERROR("Sending failed");
                return sf::Socket::Error;
            }
        }
    });
    return sf::Socket::Done;
}

sf::Socket::Status server::timeSend(){
#if DEBUG
    NETWORK_INFO("Server send function");
#endif // DEBUG
    std::for_each(clientIps.begin(), clientIps.end(), [&](sf::IpAddress client){
       if(socket.send(rawPacket, client, lastPort) != sf::Socket::Done){
            NETWORK_ERROR("Sending failed");
            return sf::Socket::Error;
       }
    });
}

void server::run() {
    NETWORK_INFO("Server running");
    while (true) {
        serverReceive();
        playerSend();
    }
}
