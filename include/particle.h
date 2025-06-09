#pragma once

#include <SFML/Graphics.hpp>

class Particle
{
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    sf::Vector2f position;
    static int nextId;
    int id;
    int x;
    int y;
    float radius;

public:
    Particle(float x, float y, float radius, sf::Color color);

    // Getters
    int getId() const { return id; }
    float getRadius() const { return radius; }
    sf::Vector2f getPosition() const { return position; }
    sf::Vector2f getVelocity() const { return velocity; }

    // Setters
    void setVelocity(const sf::Vector2f &v) { velocity = v; }
    void setPosition(const sf::Vector2f &pos)
    {
        position = pos;
        shape.setPosition(pos);
    }
    void move(const sf::Vector2f &delta)
    {
        position += delta;
        shape.move(delta);
    }
    void applyForce(const sf::Vector2f &force)
    {
        acceleration += force;
    }

    // Utility
    void update(float dt, sf::RenderWindow &window);
};
