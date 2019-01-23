#include "server.hpp"


server::server(unsigned short serverPort, int minuteToPlay, int secondToPlay):
minuteToPlay(minuteToPlay),
secondToPlay(secondToPlay)
{
    if (secondToPlay > 60)
        secondToPlay = 59;

    socket.bind(serverPort);
    socket.setBlocking(0); // just drop datagrams instead of trying to catch all of them
    NETWORK_INFO("port binded");

}


sf::Socket::Status server::serverReceive() {

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
                //NETWORK_ERROR("Sending failed");
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

        if (timerClock.getElapsedTime().asSeconds() > 1){ // every second we send a time packet
            --secondToPlay;
            if (secondToPlay <= 0 && !(minuteToPlay <= 0)){
                --minuteToPlay;
                secondToPlay = 59;
            }
            else if (secondToPlay <= 0 && minuteToPlay <= 0){
                    exit(1);
            }

            timerClock.restart(); // restart the clock
        }
#if DEBUG
        NETWORK_INFO("Time packet \n M: {} S: {}", minuteToPlay, secondToPlay);
#endif // DEBUG

        timePacket << "time" << minuteToPlay << secondToPlay; // constructing time packet
        timeSend();
    }
}

