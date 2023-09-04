#include <iostream>
#include <cstddef>
#include <SFML/Network.hpp>

#include <string>

#define myport 8000

sf::IpAddress clientip;// = ip;
unsigned short clientport;// = uport; 

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

   

    std::string data = "hello world";
    /*
    while(1)
    {

        std::cout << "Enter value: ";
        std::getline(std::cin,data);

        sf::Packet packet;
        packet << value;

        sf::IpAddress recipient = clientip;
        unsigned short port = clientport;

        sf::Packet pack;
        pack << data;

        if(socket.send(pack, recipient, port) != sf::Socket::Done)
        {
            std::cout << "not send" << std::endl;
        }
    }
    */
    
   /*
    //////////////////
    {

        sf::Packet packet;
        
        std::string con;
        sf::Packet pack;

        if (socket.receive(pack, clientip, clientport) == sf::Socket::Done)
        {
            pack >> con;
            std::cout << "Data: " << con << " bytes from ip: " << clientip << " on port " << clientport << std::endl;
        }
        if(con == "connect")
        {
            std::cout << "connect success to "<< clientip << ":" << clientport << std::endl;
        }

    }
    //////////////////
    */
    float dataX = 0;
    float dataY = 0;

    

    

    while(1)
    {
        

        std::string ReceiveConnect;    
        sf::Packet ConPack;
        if (socket.receive(ConPack, clientip, clientport) == sf::Socket::Done)
        {
            ConPack >> ReceiveConnect;
            std::cout << "ReceiveConnect: " << ReceiveConnect << "\tfrom ip: " << clientip << "\ton port: " << clientport << std::endl;
        }

        if(ReceiveConnect == "Connect")
        {
            std::cout << "im connect c:" << std::endl;
        }
        if(ReceiveConnect == "Disconect")
        {
            std::cout << "im dead :c" << std::endl;
            //system("sleep 5;");
        }
        if(ReceiveConnect == "GameData")
        {
            sf::Packet pack;
            if (socket.receive(pack, clientip, clientport) == sf::Socket::Done)
            {
                pack >> dataX >> dataY;
                std::cout << "DataX: " << dataX << "\tdataY: " << dataY << "\tfrom ip: " << clientip << "\ton port: " << clientport << std::endl;
            }
            sf::Packet packsend;
            std::string dataa = "DATA";
            packsend << dataa;
            socket.send(packsend, clientip, clientport);
        }
        
    }
	return 0;
}