#include "particle.h"

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
        velocity.x *= -1; // bounce
    }
    else if (pos.x + diameter > winWidth)
    {
        pos.x = winWidth - diameter;
        velocity.x *= -1;
    }

    if (pos.y < 0.f)
    {
        pos.y = 0.f;
        velocity.y *= -1;
    }
    else if (pos.y + diameter > winHeight)
    {
        pos.y = winHeight - diameter;
        velocity.y *= -1;
    }

    shape.setPosition(pos);
    acceleration = sf::Vector2f(0.f, 0.f); // reset after each frame
}

void Particle::applyForce(const sf::Vector2f &force)
{
    acceleration += force;
}