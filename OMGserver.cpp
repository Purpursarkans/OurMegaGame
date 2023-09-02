#include "HEAD.HPP"

int main()
{
    sf::UdpSocket socket;

    // bind the socket to a port
    if (socket.bind(54000) != sf::Socket::Done)
    {
        // error...
    }


    char data[100] = {1,2,3};

    sf::IpAddress recipient = "192.168.0.5";
    unsigned short port = 54000;
    if (socket.send(data, 100, recipient, port) != sf::Socket::Done)
    {
        // error...
    }
}