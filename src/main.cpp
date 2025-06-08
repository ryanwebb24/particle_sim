#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "particle.h"
#include "globals.h"
#include <cmath>

bool checkCollision(const Particle &a, const Particle &b)
{
    sf::Vector2f diff = a.getPosition() - b.getPosition();
    float distSq = diff.x * diff.x + diff.y * diff.y;
    float r = a.getRadius() + b.getRadius();
    return distSq < r * r;
}

void resolveCollision(Particle &a, Particle &b)
{
    sf::Vector2f delta = a.getPosition() - b.getPosition();
    float dist = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    if (dist == 0.f)
        return;

    sf::Vector2f normal = delta / dist;

    // --- Velocity resolution ---
    sf::Vector2f relVel = a.getVelocity() - b.getVelocity();
    float velAlongNormal = relVel.x * normal.x + relVel.y * normal.y;
    if (velAlongNormal > 0)
        return;

    float restitution = ELASTIC_RESTITUTION;
    float j = -(1 + restitution) * velAlongNormal;
    j /= 2.0f;

    sf::Vector2f impulse = j * normal;
    a.setVelocity(a.getVelocity() + impulse);
    b.setVelocity(b.getVelocity() - impulse);

    // --- Positional correction ---
    float penetration = a.getRadius() + b.getRadius() - dist;
    sf::Vector2f correction = (penetration / 2.f) * normal;
    a.setPosition(a.getPosition() + correction);
    b.setPosition(b.getPosition() - correction);
}

int main()
{
    // Step 1: Create a window
    unsigned int width = 800;
    unsigned int height = 600;
    sf::RenderWindow window(sf::VideoMode({width, height}), "One Dot Example");
    std::vector<Particle> particles;

    for (int i = 0; i < 100; ++i)
    {
        const int gridsize = 10;
        int xpos = i % gridsize;
        int ypos = i / gridsize;

        particles.emplace_back(100.f + (xpos * 30) + i, 200.f + (ypos * 30), 30.f, sf::Color::Red);
    }

    sf::Clock clock;

    // Step 3: Main loop
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        float dt = clock.restart().asSeconds();

        for (auto &p : particles)
        {
            p.applyForce({0.f, GRAVITY});
            // Gravity in +y direction
            p.update(dt, window);
        }

        for (size_t i = 0; i < particles.size(); ++i)
        {
            for (size_t j = i + 1; j < particles.size(); ++j)
            {
                if (checkCollision(particles[i], particles[j]))
                {
                    // Basic elastic bounce (we’ll improve this later)
                    resolveCollision(particles[i], particles[j]);
                }
            }
        }

        // Step 4: Clear, draw, and display
        window.clear(sf::Color::Black); // Clear screen to black
        for (auto &p : particles)
        {
            p.draw(window); // Draw the particle
        }

        window.display(); // Show everything on screen
    }

    return 0;
}
