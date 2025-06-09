#include "particle.h"
#include "globals.h"

// TODO: for collisions store the position of each particle when we run the update method.
// Then at the end we need to do spatial partitioning to devide the grid into groups so that i only check colisions of items in that group

int Particle::nextId = 0;

Particle::Particle(float x, float y, float radius, sf::Color color)
    : id(nextId++), x(x), y(y), position(x, y), radius(radius)
{
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setPosition({x, y});
}

void Particle::update(float dt, sf::RenderWindow &window)
{
    velocity += acceleration * dt;
    move(velocity * dt);

    sf::Vector2f pos = position;
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
        position.x = winWidth - diameter;
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

    setPosition(pos);
    acceleration = sf::Vector2f(0.f, 0.f); // reset after each frame
    // draw shape at end of update
    window.draw(shape);
}