#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

#include "particle.h"
#include "globals.h"
#include "collisions.h"

int main()
{
    // Step 1: Create a window
    unsigned int width = 1800;
    unsigned int height = 1000;
    sf::RenderWindow window(sf::VideoMode({width, height}), "One Dot Example");
    std::vector<Particle> particles;

    // initialize vector with particles
    const int numberOfParticles = 1000;
    for (int i = 0; i < numberOfParticles; ++i)
    {
        const int gridsize = std::ceil(sqrt(numberOfParticles));
        int xpos = i % gridsize;
        int ypos = i / gridsize;

        particles.emplace_back(100.f + (xpos * 10) + i, 200.f + (ypos * 10), 5.f, sf::Color::Red);
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

        // Step 4: Clear, draw, and display
        window.clear(sf::Color::Black); // Clear screen to black

        getCollisions(particles);

        for (auto &p : particles)
        {
            // applying gravity every time
            p.applyForce({0.f, GRAVITY});
            // make sure to update
            p.update(dt, window);
        }

        window.display(); // Show everything on screen
    }

    return 0;
}
