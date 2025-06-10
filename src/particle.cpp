#include "particle.h"
#include "globals.h"
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

void Particle::handleWallCollision(const sf::RenderWindow &window)
{
    sf::Vector2f pos = position;
    float diameter = radius * 2;

    // Window bounds
    float winWidth = static_cast<float>(window.getSize().x) - WINDOW_PADDING;
    float winHeight = static_cast<float>(window.getSize().y) - WINDOW_PADDING;

    if (pos.x < WINDOW_PADDING)
    {
        pos.x = WINDOW_PADDING;
        velocity.x *= -ELASTIC_RESTITUTION; // bounce
    }
    else if (pos.x + diameter > winWidth)
    {
        position.x = winWidth - diameter;
        velocity.x *= -ELASTIC_RESTITUTION;
    }

    if (pos.y < WINDOW_PADDING)
    {
        pos.y = WINDOW_PADDING;
        velocity.y *= -ELASTIC_RESTITUTION;
    }
    else if (pos.y + diameter > winHeight)
    {
        pos.y = winHeight - diameter;
        velocity.y *= -ELASTIC_RESTITUTION;
    }

    // clamp position just in case
    pos.x = std::max(WINDOW_PADDING, std::min(pos.x, winWidth - diameter));
    pos.y = std::max(WINDOW_PADDING, std::min(pos.y, winHeight - diameter));
    setPosition(pos);
}

void Particle::update(float dt, sf::RenderWindow &window)
{
    velocity += acceleration * dt;
    move(velocity * dt);

    handleWallCollision(window);

    acceleration = sf::Vector2f(0.f, 0.f); // reset after each frame
    // draw shape at end of update
    window.draw(shape);
}