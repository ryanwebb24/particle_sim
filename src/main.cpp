#include <SFML/Graphics.hpp>
#include <iostream>
#include "particle.h"
#include "globals.h"

int main()
{
    // Step 1: Create a window
    unsigned int width = 800;
    unsigned int height = 600;
    sf::RenderWindow window(sf::VideoMode({width, height}), "One Dot Example");

    // Step 2: Create a circle shape (the "dot")
    // sf::CircleShape dot(5.0f); // 10 pixel radius
    // dot.setFillColor(sf::Color::Red);
    // dot.setPosition(100.0f, 100.0f); // Top-left position
    Particle p(100.0f, 100.0f, 5.f, sf::Color::Red);

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

        // Apply gravity
        p.applyForce({0.f, GRAVITY});

        // Update with boundary logic
        p.update(dt, window);

        // Step 4: Clear, draw, and display
        window.clear(sf::Color::Black); // Clear screen to black
        p.draw(window);                 // Draw the particle
        window.display();               // Show everything on screen
    }

    return 0;
}
