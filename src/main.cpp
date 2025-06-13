#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

#include "collisions.h"
#include "globals.h"
#include "particle.h"

std::vector<Particle> initParticles(int width, int height) {
    std::vector<Particle> particles;

    // initialize vector with particles
    const int numberOfParticles = 10000;
    const int gridCols = std::ceil(std::sqrt(numberOfParticles));
    const int gridRows = std::ceil(numberOfParticles / static_cast<float>(gridCols));
    float availableWidth = width - 2 * WINDOW_PADDING;
    float availableHeight = height - 2 * WINDOW_PADDING;

    float cellWidth = availableWidth / gridCols;
    float cellHeight = availableHeight / gridRows;
    float particleRadius = 1.f;  // leave gap between particles

    particles.reserve(numberOfParticles);
    for (int i = 0; i < numberOfParticles; ++i) {
        int col = i % gridCols;
        int row = i / gridCols;

        float xOffset = (row % 2 == 0) ? 0.f : cellWidth / 2.f;
        float x = WINDOW_PADDING + col * cellWidth + xOffset + cellWidth / 2.f;
        float y = WINDOW_PADDING + row * cellHeight + cellHeight / 2.f;

        particles.emplace_back(x, y, particleRadius, sf::Color::Red);
    }
    return particles;
}

int main() {
    // Step 1: Create a window
    unsigned int width = 1800;
    unsigned int height = 1000;
    sf::RenderWindow window(sf::VideoMode({width, height}), "One Dot Example");

    std::vector<Particle> particles = initParticles(width, height);

    std::vector<Particle> mouseParticle(0.f, 0.f, 10.f, sf::Color::White);

    sf::Clock deltaClock;
    sf::Clock fpsClock;
    int frameCount = 0;
    bool hasRun = false;

    // Step 3: Main loop
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        float dt = deltaClock.restart().asSeconds();

        frameCount++;
        if (fpsClock.getElapsedTime().asSeconds() >= 1.0f) {
            float fps = frameCount / fpsClock.getElapsedTime().asSeconds();
            frameCount = 0;
            fpsClock.restart();

            // Update the window title
            window.setTitle("Particle Simulation - FPS: " + std::to_string(static_cast<int>(fps)));
        }

        // Step 4: Clear, draw, and display
        window.clear(sf::Color::Black);  // Clear screen to black

        PARTICLE_GRID.clear();

        for (auto &p : particles) {
            // applying gravity every time
            p.applyForce({0.f, GRAVITY});
            // make sure to update
            p.update(dt, window);
        }
        getCollisions();

        window.display();  // Show everything on screen
    }

    return 0;
}
