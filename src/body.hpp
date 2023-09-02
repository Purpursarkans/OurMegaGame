#include "main.hpp"

class Body
{
    public:
    const sf::Vector2f &applyForce(const sf::Vector2f &force);
    const sf::Vector2f &applyForce(float x, float y);
    const sf::Vector2f &applyForce(int x, int y);

    const sf::Vector2f &setVelocityX(float x);
    const sf::Vector2f &setVelocityY(float y);

    const sf::Vector2f &setVelocity(const sf::Vector2f &new_velocity);
    const sf::Vector2f &setVelocity(float x, float y);

    const sf::Vector2f &getVelocity();

    void process(float dt);

    const sf::Vector2f &getPosition();
    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f &position);

    Body(
        sf::Sprite *sprite,
        sf::Vector2f speed,
        sf::Vector2f initial_velocity, 
        sf::Vector2f target_velocity
    );

    private:
    sf::Vector2f speed;
    sf::Vector2f velocity;
    sf::Vector2f target_velocity;
    sf::Sprite *sprite;
};