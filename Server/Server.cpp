#include <iostream>
#include <cstddef>
#include <SFML/Network.hpp>

#include <string>

#define myport 8000

sf::IpAddress clientip;// = ip;
unsigned short clientport;// = uport; 

void RecCon(sf::UdpSocket &socket, sf::Packet &ReceivePacket, sf::Packet &SendPacket, std::vector<sf::IpAddress> &ConnectionsIp, std::vector<unsigned short> &ConnectionsPort)
{
    sf::Packet pack;
    socket.receive(ReceivePacket, clientip, clientport);

    for (int i = 0; i < ConnectionsPort.size(); i++) 
    {
        if(ConnectionsPort[i] == clientport)
        {
            continue;
        }
        socket.send(SendPacket, ConnectionsIp[i], ConnectionsPort[i]);
    }
}


int main()
{
  std::cout << "==== Project UDP ====\n";
    
    sf::UdpSocket socket;

    if (socket.bind(myport) != sf::Socket::Done)
    {
        std::cout << "error bind port " << myport << " :c";
        system("sleep 3600; pause");
    }

    int value = 0;

    std::cout << "\n*** Server Created ***\n";

    float dataX = 0;
    float dataY = 0;

    
    std::vector<sf::IpAddress> ConnectionsIp;
    std::vector<unsigned short> ConnectionsPort;

    while(1)
    {
        std::string ReceiveConnect;    
        sf::Packet ConPack;
        if (socket.receive(ConPack, clientip, clientport) == sf::Socket::Done)
        {
            ConPack >> ReceiveConnect;
            //std::cout << "ReceiveConnect: " << ReceiveConnect << "\tfrom ip: " << clientip << "\ton port: " << clientport << std::endl;
        }

        if(ReceiveConnect == "Client try connect")
        {
            sf::Packet SendConPac;
            std::string SendConnect = "Server connect";
            SendConPac << SendConnect;
            socket.send(SendConPac, clientip, clientport);

            std::cout << "im connect from ip: "<< clientip << " port: " << clientport << " c:" << std::endl;
            ConnectionsIp.push_back(clientip);
            ConnectionsPort.push_back(clientport);
            //system("sleep 1");
        }
        if(ReceiveConnect == "Disconect")
        {
            std::cout << "im dead :c" << "ip:" << clientip << ":" << clientport << std::endl;
        }
        if(ReceiveConnect == "GameData")
        {   
            sf::Packet pack;
            std::string data;
            
            //RecCon(socket, pack, packsend, ConnectionsIp, ConnectionsPort);

            socket.receive(pack, clientip, clientport);
            //std::cout << "DataX: " << dataX << "\tdataY: " << dataY << "\tfrom ip: " << clientip << "\ton port: " << clientport << std::endl;

            for (int i = 0; i < ConnectionsPort.size(); i++) 
            {
                if(ConnectionsPort[i] == clientport)
                {
                    continue;
                }
                socket.send(pack, ConnectionsIp[i], ConnectionsPort[i]);
                std::cout << "packet send to: " << ConnectionsIp[i] << ":" << ConnectionsPort[i] << std::endl;
            }
        }
    }
  return 0;
}