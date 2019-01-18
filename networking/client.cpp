//
// Created by ramon on 15-1-2019.
//
#include "client.hpp"

clientConnect::clientConnect(sf::IpAddress server_ip, unsigned short port):
    server_ip(server_ip),
    port(port)
    {
        if (socket.bind(port) != sf::Socket::Done){
            TF_WARN("Failed to connect to server");
        }
        std::string tmp;
#ifdef _WIN32

    system("netsh interface ip show config name = \"Wi-Fi\" | findstr \"Ip Address\" >ip.txt");

#elif __APPLE__
    system("ifconfig en0 | grep inet | awk '{print $2'>ip.txt");
}
#endif
    std::sting tmp;
    std::ifstream input;
    input.open("ip.txt");
    if (input.is_open()){
        input>>tmp;
    }
    std::string ip;
    std::for_each(tmp.begin(), tmp.end(), [&ip](char &c) {if (!isalpha(c)&&c !=' ' &&c !=':') { ip += c; }});
    my_ip=ip;
}


void clientConnect::send(tf::network_packet){
    sf::Packet raw_package;
    raw_package << packet.ip_sender << packet.x <<packet.y <<packet.rotation <<packet.firing <<packet.nickname;
    if (socket::send(raw_package)){
        NETWORK_INFO("package send");
    }
}

void clientConnect::receive(){
     sf::Packet raw_packet;
     sock.receive(raw_packet);
     tf::network_packet packet;
     if( raw_packet >> receivedPacket.ip_sender >> receivedPacket.x >>receivedPacket.y >>receivedPacket.rotation >>receivedPacket.firing >>receivedPacket.nickname ){
         NETWORK_INFO("Received package");
     }
     else{
         NETWORK_INFO("No package received");
     }

 }

