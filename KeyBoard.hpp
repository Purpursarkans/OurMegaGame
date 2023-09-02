#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include "HEAD.HPP"

struct POINT
{
    double x;
    double y;
};

class KeyBoardAction
{
public:
    POINT KeyBoardCheck(float time)
    {
        POINT point;
        point.x = 0;
        point.y = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            point.x = -1*time;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            point.x = 1*time;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            point.y = -1*time;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            point.y = 1*time;
        }
        return point;
    }
private:



};

#endif