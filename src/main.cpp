#include <SFML/Graphics.hpp>
#include <iostream>
#include "particle.h"

int main()
{
    // Step 1: Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "One Dot Example");

    // Step 2: Create a circle shape (the "dot")
    // sf::CircleShape dot(5.0f); // 10 pixel radius
    // dot.setFillColor(sf::Color::Red);
    // dot.setPosition(100.0f, 100.0f); // Top-left position
    Particle p(100.0f, 100.0f, 5.f, sf::Color::Red);

    // Step 3: Main loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::W:
                    p.move(0, -5);
                    break;
                case sf::Keyboard::A:
                    p.move(-5, 0);
                    break;
                case sf::Keyboard::S:
                    p.move(0, 5);
                    break;
                case sf::Keyboard::D:
                    p.move(5, 0);
                    break;

                default:
                    break;
                }
            }
        }

        // Step 4: Clear, draw, and display
        window.clear(sf::Color::Black); // Clear screen to black
        p.draw(window);                 // Draw the particle
        window.display();               // Show everything on screen
    }

    return 0;
}
