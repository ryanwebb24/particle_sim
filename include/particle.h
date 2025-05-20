#pragma once

#include <SFML/Graphics.hpp>

class Particle
{
public:
    Particle(float x, float y, float radius, sf::Color color);

    void draw(sf::RenderWindow &window);
    void update(float dt, const sf::RenderWindow &window);
    void applyForce(const sf::Vector2f &force);
    int getId() const { return id; }

private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    static int nextId;
    int id;
};
