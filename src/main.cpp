#include "main.hpp"
#include "renderer.hpp"
#include "body.hpp"

int myport = 8001;
const int serverport = 8000;
const sf::IpAddress serverip = "127.0.0.1";

static int WINDOW_WIDTH = 1280;
static int WINDOW_HEIGHT = 720;

static bool up, left, down, right;

sf::UdpSocket socket;

void DisconnectAfterExit()
{
    	
    sf::Packet SendConPac;
    std::string SendConnect = "Disconect";
    SendConPac << SendConnect;

    sf::IpAddress recipient = serverip;
    unsigned short port = serverport;

    socket.send(SendConPac, recipient, port);
}

float length(sf::Vector2f v)
{
    return sqrt(v.x*v.x+v.y*v.y);
}

sf::Vector2f norm(sf::Vector2f v)
{
    float len = length(v);
    return sf::Vector2f(v.x/len, v.y/len);
}

void handleControls(sf::Event event)
{
    bool val;
    if (event.type == sf::Event::KeyPressed)
    {
        val = true;
    }
    else if (event.type == sf::Event::KeyReleased)
    {
        val = false;
    }

    auto c = event.key.code;
    if (c == sf::Keyboard::W) up = val;
    if (c == sf::Keyboard::A) left = val;
    if (c == sf::Keyboard::S) down = val;
    if (c == sf::Keyboard::D) right = val;
    // std::cout << c << std::endl;
}

void log(sf::Vector2f v)
{
    std::cout << v.x << " : " << v.y << std::endl;
}

int main()
{
    atexit(DisconnectAfterExit);
    std::cout << "Init" << std::endl;

    std::vector<float> fps_avg;
    float fps, fps_min, fps_max;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "OMG", sf::Style::Close);

    Renderer r(window);
    std::map<std::string, sf::Texture> textures = r.loadImagesFromFolder("assets/");
    auto CHAR_SPRITE = r.newSprite(&textures["char.png"]);

    sf::Font font;
    if (!font.loadFromFile("assets/text.ttf"))
    {
        std::cerr << "text.ttf not found" << std::endl;        
    }

    auto player = Body(
        &CHAR_SPRITE,
        sf::Vector2f(5.f, 5.f),
        VECTOR2F_ZERO,
        sf::Vector2f(150.f, 150.f)
    );

    ////////////////////////////////////////////////////////////////////////////////////////
    sf::Socket::Status status;
    sf::Packet SendConPac;
    do
    {
        status = socket.bind(myport);
    } while (status != sf::Socket::Done && myport++);

    std::string SendConnect = "Connect";
    SendConPac << SendConnect;

    sf::IpAddress recipient = serverip;
    unsigned short port = serverport;

    socket.send(SendConPac, serverip, serverport);

    ////////////////////////////////////////////////////////////////////////////////////////

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::X)
            {
                player.applyForce(1000.f, 0.f);
            }
            else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::R)
            {
                player.setPosition(100.f, 100.f);
                player.setVelocity(VECTOR2F_ZERO);
            }
            handleControls(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float s = elapsed.asSeconds();
        std::stringstream text;

        if (fps_avg.size() > 100) 
        {
            fps_avg.erase(fps_avg.begin());
            fps = (int) std::accumulate(fps_avg.begin(), fps_avg.end(), 0.f) / fps_avg.size();
            if (fps > fps_max && fps < 100000.f) fps_max = (int)fps;
            else if (fps < fps_min && fps > 24.f) fps_min = (int)fps;
        }

        fps_avg.push_back(1/s);
        text << "Frame time: " << s << "\n";
        text << "+ FPS: " << fps << "\n";
        text << "+ MIN: " << fps_min << "\n";
        text << "+ MAX: " << fps_max << "\n";

        auto pv = player.getVelocity();
        text << "Velocity" << "\n";
        text << "+ X " << pv.x << "\n";
        text << "+ Y " << pv.y << "\n";


        ////////////////////////////////////////////////////////////////////////////////////////

        sf::Packet GameData;
        std::string SendData = "GameData";
        GameData << SendData;
        socket.send(GameData, recipient, port);

        float dataX = pv.x;
        float dataY = pv.y;
        sf::Packet packet;
        packet << dataX << dataY;
        socket.send(packet, recipient, port);

        
        std::string ReceiveConnect;    
        sf::Packet ConPack;
        socket.receive(ConPack, recipient, port);
        ConPack >> ReceiveConnect;
        std::cout << "ReceiveConnect: " << ReceiveConnect << "\tfrom ip: " << recipient << "\ton port: " << port << std::endl;


        ////////////////////////////////////////////////////////////////////////////////////////


        // sf::Vector2f viewport_target;

        if (right) player.applyForce(2, 0);
        else if (left) player.applyForce(-2, 0);
        // else {player.setVelocityX(0.f);}

        if (down) player.applyForce(0, 2);
        else if (up) player.applyForce(0, -2);
        // else player.setVelocityY(0.f);

        auto vvec = r.viewport.getCenter() - player.getPosition(); 
        auto vdist = length(vvec);
        text << "Viewport distance: " << vvec.x << " " <<vvec.y << "\n";
        text << "+ Length " << vdist << "\n";

        // float vm = 1.01f * s * vdist;
        // if (vdist > 5.f) r.viewport.move(viewport_target.x * vm, viewport_target.y * vm);
        r.viewport.move(-vvec * s);

        player.process(s);

        window.clear();

        sf::Text texto;
        texto.setPosition(r.viewport.getCenter()-(r.viewport.getSize()/2.f));
        texto.setFont(font);
        texto.setString(text.str());

        window.draw(texto);
        r.render();
        window.display();
    }

    return 0;
}