#pragma once

#include <SFML/Graphics.hpp>

class Particle
{
public:
    Particle(float x, float y, float radius, sf::Color color);

    void draw(sf::RenderWindow &window);
    void move(float x, float y);

private:
    sf::CircleShape shape;
};
