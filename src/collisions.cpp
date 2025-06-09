#include "collisions.h"

#include <iostream>
#include "particle.h"

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