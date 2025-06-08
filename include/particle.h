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
    // sf::Vector2f getPosition() {return }
    sf::Vector2f getPosition() const { return shape.getPosition(); }
    float getRadius() const { return shape.getRadius(); }

    sf::Vector2f getVelocity() const { return velocity; }
    void setVelocity(const sf::Vector2f &v) { velocity = v; }
    void setPosition(const sf::Vector2f &pos) { shape.setPosition(pos); }

private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    static int nextId;
    int id;
};
