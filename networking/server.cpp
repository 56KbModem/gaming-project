#include "Server.hpp"


Server::Server(const unsigned short & ServerPort, int & minutes, int & seconds):
minuteToPlay(minutes),
secondToPlay(seconds)
{
    /* revert time back */
    if (secondToPlay > 60)
        secondToPlay = 59;

    if (minuteToPlay > 60)
        minuteToPlay = 59;

    socket.bind(ServerPort);
    socket.setBlocking(0); // just drop datagrams instead of trying to catch all of them
    NETWORK_INFO("port binded");

}


sf::Socket::Status Server::ServerReceive() {
    std::string tmpHeader;
    if (socket.receive(playerPacket, lastIp, lastPort) != sf::Socket::Done) {
#if DEBUG
        //NETWORK_INFO("received nothing");
#endif // DEBUG
        return sf::Socket::NotReady;
    }
    playerPacket>>tmpHeader ;
    if (tmpHeader == "leave"&& !clientIps.empty()){
        clientIps.erase(lastIp);
    }
    else{
#if DEBUG
   // NETWORK_INFO("Received data");
#endif // DEBUG
    clientIps.insert(lastIp);
    return sf::Socket::Done;
    }
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
        timePacket.clear();
        timePacket << "time" << 0 << 0; // stop the clients
        exit(1);
    }

    timePacket.clear(); // clear the packet, otherwise we keep the same data...

    if (timePacket << "time" << minuteToPlay << secondToPlay) {  // constructing time packet
#if DEBUG
        NETWORK_INFO("Packet created");
#endif
    }

#if DEBUG
    NETWORK_INFO("Time packet: M: {} S: {}", minuteToPlay, secondToPlay);
#endif // DEBUG

    std::for_each(clientIps.begin(), clientIps.end(), [&](sf::IpAddress client){
       if(socket.send(timePacket, client, 53000) != sf::Socket::Done){
#if DEBUG
            NETWORK_ERROR("Sending failed to client: {}:{}", client, lastPort);
#endif // DEBUG
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
       sf::sleep(sf::milliseconds(1));
    }
}