#include "body.hpp"

const sf::Vector2f &Body::applyForce(const sf::Vector2f &force)
{
    velocity += force;
    return velocity;
}

const sf::Vector2f &Body::applyForce(float x, float y)
{
    return applyForce(sf::Vector2f(x, y));
}

const sf::Vector2f &Body::applyForce(int x, int y)
{
    return applyForce(sf::Vector2f(
        speed.x * x,
        speed.y * y
    ));
}

const sf::Vector2f &Body::getVelocity()
{
    return velocity;
}

void Body::process(float dt)
{
    if (velocity != VECTOR2F_ZERO)
    {
        auto vn = norm(velocity);

        if (velocity.x < target_velocity.x && velocity.x > -target_velocity.x)
        {
            velocity.x -= vn.x * speed.x / 2 * (dt*100);
        }
        if (velocity.y < target_velocity.y && velocity.y > -target_velocity.y)
        {
            velocity.y -= vn.y * speed.y / 2 * (dt*100);
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
            velocity.x -= roundf(vn.x) * speed.x * 2;
        }
        if (velocity.y >= target_velocity.y || velocity.y <= -target_velocity.y)
        {
            velocity.y -= roundf(vn.y) * speed.y * 2;
        }
    }

    sprite->move(
        velocity.x * dt,
        velocity.y * dt
    );

}

const sf::Vector2f &Body::setVelocityX(float x)
{
    velocity.x = x;
    return velocity;
}
const sf::Vector2f &Body::setVelocityY(float y)
{
    velocity.y = y;
    return velocity;
}

const sf::Vector2f &Body::setVelocity(const sf::Vector2f &new_velocity)
{
    velocity = new_velocity;
    return velocity;
}
const sf::Vector2f &Body::setVelocity(float x, float y)
{
    return setVelocity(sf::Vector2f(x,y));
}

Body::Body(
    sf::Sprite *sprite, 
    sf::Vector2f speed,
    sf::Vector2f initial_velocity, 
    sf::Vector2f target_velocity
) : sprite(sprite), speed(speed), velocity(initial_velocity), target_velocity(target_velocity) 
{
    if (speed.x > target_velocity.x || speed.y > target_velocity.y)
    {
        std::cerr << "Speed axis is more than target velocity axis! > Unexpected behaviour" << std::endl;
    }
}

const sf::Vector2f &Body::getPosition() 
{
    return sprite->getPosition();
}

void Body::setPosition(float x, float y)
{
    sprite->setPosition(x, y);
}

void Body::setPosition(const sf::Vector2f& position)
{
    sprite->setPosition(position);
}