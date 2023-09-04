#pragma once
#define VECTOR2F_ZERO sf::Vector2f(0.f, 0.f)
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include <math.h>
#include <sstream>
#include <numeric>

float length(sf::Vector2f v);
sf::Vector2f norm(sf::Vector2f v);

// template <typename T>
// class vec2
// {
//     public:
//     T x, y;

//     vec2<T> normalize();
//     vec2<T> dot();

//     vec2<T>(T x, T y);


// };