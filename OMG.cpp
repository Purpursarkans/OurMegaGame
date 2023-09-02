#include "HEAD.HPP"

static int WINDOW_WIDTH = 1280;
static int WINDOW_HEIGHT = 720;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "OMG", sf::Style::Close);
    
    
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Magenta);


    sf::Clock clock;

    while (window.isOpen())
    {   

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/1600;

        sf::Event event;
        while (window.pollEvent(event))
        {
            
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();


        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}