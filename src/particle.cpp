#include "particle.h"
#include "globals.h"

// TODO: for collisions store the position of each particle when we run the update method.
// Then at the end we need to do spatial partitioning to devide the grid into groups so that i only check colisions of items in that group

Particle::Particle(float x, float y, float radius, sf::Color color)
{
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setPosition({x, y});
}

void Particle::draw(sf::RenderWindow &window)
{
    window.draw(shape);
}

void Particle::update(float dt, const sf::RenderWindow &window)
{
    velocity += acceleration * dt;
    shape.move(velocity * dt);

    sf::Vector2f pos = shape.getPosition();
    float radius = shape.getRadius();
    float diameter = radius * 2;

    // Window bounds
    float winWidth = static_cast<float>(window.getSize().x);
    float winHeight = static_cast<float>(window.getSize().y);

    if (pos.x < 0.f)
    {
        pos.x = 0.f;
        velocity.x *= -ELASTIC_RESTITUTION; // bounce
    }
    else if (pos.x + diameter > winWidth)
    {
        pos.x = winWidth - diameter;
        velocity.x *= -ELASTIC_RESTITUTION;
    }

    if (pos.y < 0.f)
    {
        pos.y = 0.f;
        velocity.y *= -ELASTIC_RESTITUTION;
    }
    else if (pos.y + diameter > winHeight)
    {
        pos.y = winHeight - diameter;
        velocity.y *= -ELASTIC_RESTITUTION;
    }

    shape.setPosition(pos);
    acceleration = sf::Vector2f(0.f, 0.f); // reset after each frame
}

void Particle::applyForce(const sf::Vector2f &force)
{
    acceleration += force;
}