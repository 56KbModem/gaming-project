#include "Server.hpp"


Server::Server(unsigned short ServerPort, int minuteToPlay, int secondToPlay):
minuteToPlay(minuteToPlay),
secondToPlay(secondToPlay)
{
    if (secondToPlay > 60)
        secondToPlay = 59;

    socket.bind(ServerPort);
    socket.setBlocking(0); // just drop datagrams instead of trying to catch all of them
    NETWORK_INFO("port binded");

}


sf::Socket::Status Server::ServerReceive() {

    if (socket.receive(playerPacket, lastIp, lastPort) != sf::Socket::Done) {
#if DEBUG
        //NETWORK_INFO("received nothing");
#endif // DEBUG
        return sf::Socket::NotReady;
    }
#if DEBUG
   // NETWORK_INFO("Received data");
#endif // DEBUG
    clientIps.insert(lastIp);
    return sf::Socket::Done; 
}

sf::Socket::Status Server::playerSend() {
#if DEBUG
    //NETWORK_INFO("Server send function");
#endif // DEBUG
    std::for_each(clientIps.begin(), clientIps.end(), [&](sf::IpAddress client){
        if (client != lastIp) {
            if (socket.send(playerPacket, client, lastPort) != sf::Socket::Done) {
                //NETWORK_ERROR("Sending failed");
                return sf::Socket::Error;
            }
        }
    });
    return sf::Socket::Done;
}

sf::Socket::Status Server::timeSend(){
#if DEBUG
    //NETWORK_INFO("Server send function");
#endif // DEBUG
    --secondToPlay;
    if (secondToPlay <= 0 && minuteToPlay > 0) {
        --minuteToPlay;
        secondToPlay = 59;
    } else if (secondToPlay <= 0 && minuteToPlay <= 0) {
        exit(1);
    }

    timePacket.clear(); // clear the packet, otherwise we keep the same data...

    if (timePacket << "time" << minuteToPlay << secondToPlay) {  // constructing time packet
        NETWORK_INFO("Packet created");
    }

#if DEBUG
    NETWORK_INFO("Time packet: M: {} S: {}", minuteToPlay, secondToPlay);
#endif // DEBUG

    std::for_each(clientIps.begin(), clientIps.end(), [&](sf::IpAddress client){
       if(socket.send(timePacket, client, 53000) != sf::Socket::Done){
            NETWORK_ERROR("Sending failed to client: {}:{}", client, lastPort);
            return sf::Socket::Error;
       }
    });
}

void Server::run() {
    NETWORK_INFO("Server running");

    while (true) {
        ServerReceive();
        playerSend();
        if (timerClock.getElapsedTime().asSeconds() > 1) { // every second we send a time packet
            timeSend();
            timerClock.restart(); // restart the clock
        }

    }
}

