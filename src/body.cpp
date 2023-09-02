#include "body.hpp"

const sf::Vector2f &Body::applyForce(const sf::Vector2f &force)
{
    this->velocity += force;
    return this->velocity;
}

const sf::Vector2f &Body::applyForce(float x, float y)
{
    return this->applyForce(sf::Vector2f(x, y));
}

const sf::Vector2f &Body::applyForce(int x, int y)
{
    return this->applyForce(sf::Vector2f(
        this->speed.x * x,
        this->speed.y * y
    ));
}

const sf::Vector2f &Body::getVelocity()
{
    return this->velocity;
}

sf::Vector2f normalize(const sf::Vector2f& source)
{
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0)
        return sf::Vector2f(source.x / length, source.y / length);
    else
        return source;
}

void Body::process(float dt)
{
    if (velocity != VECTOR2F_ZERO)
    {
        auto norm = normalize(velocity);
        std::cout << norm.x << " " << norm.y << " ; " << roundf(norm.x) << " " << roundf(norm.y) << std::endl;

        if (velocity.x < target_velocity.x && velocity.x > -target_velocity.x)
        {
            velocity.x -= norm.x * speed.x / 2;
        }
        if (velocity.y < target_velocity.y && velocity.y > -target_velocity.y)
        {
            velocity.y -= norm.y * speed.y / 2;
        }

        if (velocity.x < speed.x && velocity.x > -speed.x)
        {
            velocity.x = 0.f;
        }
        if (velocity.y < speed.y && velocity.y > -speed.y)
        {
            velocity.y = 0.f;
        }

        if (velocity.x >= target_velocity.x || velocity.x <= -target_velocity.x)
        {
            velocity.x -= roundf(norm.x) * speed.x * 2;
        }
        if (velocity.y >= target_velocity.y || velocity.y <= -target_velocity.y)
        {
            velocity.y -= roundf(norm.y) * speed.y * 2;
        }
    }
    // std::cout << velocity.x << " " << velocity.y << std::endl;

    float x = this->velocity.x * dt;
    float y = this->velocity.y * dt;
    this->sprite->move(x,y);

}

const sf::Vector2f &Body::setVelocityX(float x)
{
    this->velocity.x = x;
    return this->velocity;
}
const sf::Vector2f &Body::setVelocityY(float y)
{
    this->velocity.y = y;
    return this->velocity;
}

const sf::Vector2f &Body::setVelocity(const sf::Vector2f &new_velocity)
{
    this->velocity = new_velocity;
    return this->velocity;
}
const sf::Vector2f &Body::setVelocity(float x, float y)
{
    return this->setVelocity(sf::Vector2f(x,y));
}

Body::Body(
    sf::Sprite *sprite, 
    sf::Vector2f speed,
    sf::Vector2f initial_velocity, 
    sf::Vector2f target_velocity
) : sprite(sprite), speed(speed), velocity(initial_velocity), target_velocity(target_velocity) 
{
    if (this->speed.x > this->target_velocity.x || this->speed.y > this->target_velocity.y)
    {
        std::cerr << "Speed axis is more than target velocity axis! > Unexpected behaviour" << std::endl;
    }
}

const sf::Vector2f &Body::getPosition() 
{
    return this->sprite->getPosition();
}

void Body::setPosition(float x, float y)
{
    this->sprite->setPosition(x, y);
}

void Body::setPosition(const sf::Vector2f& position)
{
    this->sprite->setPosition(position);
}