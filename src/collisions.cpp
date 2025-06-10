#include <iostream>
#include <cmath>

#include "particle.h"
#include "globals.h"
#include "collisions.h"

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

void getCollisions(std::vector<Particle> &particles)
{

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
}