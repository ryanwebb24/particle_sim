#include "particle.h"

Particle::Particle(float x, float y, float radius, sf::Color color)
{
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setPosition(x, y);
}

void Particle::draw(sf::RenderWindow &window)
{
    window.draw(shape);
}

void Particle::move(float x, float y)
{
    shape.move(x, y);
}