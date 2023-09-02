#include "main.hpp"
#include "renderer.hpp"
#include "body.hpp"
#include <sstream>
#include <numeric>

static int WINDOW_WIDTH = 1280;
static int WINDOW_HEIGHT = 720;

static bool up, left, down, right;

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
    std::cout << "Init" << std::endl;

    std::vector<float> fps_avg;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "OMG", sf::Style::Close);

    Renderer r(window);
    std::map<std::string, sf::Texture> textures = r.loadImagesFromFolder("assets/");
    auto CHAR_SPRITE = r.newSprite(&textures["char.png"]);
    
    auto player = Body(
        &CHAR_SPRITE,
        sf::Vector2f(5.f, 5.f),
        VECTOR2F_ZERO,
        sf::Vector2f(150.f, 150.f)
    );

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
        auto pv = player.getVelocity();

        if (fps_avg.size() > 100) fps_avg.erase(fps_avg.begin());
        fps_avg.push_back(1/s);

        text << "Frame time: " << s << "\n";
        text << "FPS: " << std::accumulate(fps_avg.begin(), fps_avg.end(), 0.f) / fps_avg.size() << "\n";
        text << "VX" << pv.x << "\n";
        text << "VY" << pv.y << "\n";
        // text << "UP: " << up << "\n";
        // text << "LEFT: " << left << "\n";
        // text << "DOWN: " << down << "\n";
        // text << "RIGHT: " << right << "\n";

        sf::Font font;
        if (!font.loadFromFile("assets/text.ttf"))
        {
            std::cerr << "text.ttf not found" << std::endl;        
        }
        sf::Text texto;
        texto.setFont(font);
        texto.setString(text.str());

        if (right) {player.applyForce(2, 0);}
        else if (left) {player.applyForce(-2, 0);}
        // else {player.setVelocityX(0.f);}

        if (down) player.applyForce(0, 2);
        else if (up) player.applyForce(0, -2);
        // else player.setVelocityY(0.f);
        
        player.process(s);

        window.clear();
        window.draw(texto);
        r.render();
        window.display();
    }

    return 0;
}