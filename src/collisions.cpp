#include "collisions.h"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <mutex>
#include <thread>

#include "globals.h"
#include "particle.h"

// Ensure resolveCollision remains the same as you had it
void resolveCollision(Particle& a, Particle& b) {
    sf::Vector2f delta = a.getPosition() - b.getPosition();
    float dist = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    if (dist == 0.f)
        return;

    sf::Vector2f normal = delta / dist;

    if (std::abs(normal.x) < 0.01f) {
        float nudge = 0.1f;
        normal.x += nudge;
        float length = std::sqrt(normal.x * normal.x + normal.y * normal.y);
        normal /= length;
    }

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

    float penetration = a.getRadius() + b.getRadius() - dist;
    sf::Vector2f correction = (penetration / 2.f) * normal;
    a.setPosition(a.getPosition() + correction);
    b.setPosition(b.getPosition() - correction);
}

// Function that runs on each thread — handles a slice of cells
void processCellsRange(const std::vector<std::pair<int, int>>& cellsToProcess) {
    for (const auto& cell : cellsToProcess) {
        auto& cellParticles = PARTICLE_GRID[cell];
        int cellX = cell.first;
        int cellY = cell.second;

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                auto neighborCell = std::make_pair(cellX + dx, cellY + dy);
                if (PARTICLE_GRID.count(neighborCell) == 0)
                    continue;

                auto& neighborParticles = PARTICLE_GRID[neighborCell];

                for (Particle* p1 : cellParticles) {
                    for (Particle* p2 : neighborParticles) {
                        if (p1 == p2 || p1->id > p2->id) continue;  // prevent double handling

                        sf::Vector2f diff = p1->getPosition() - p2->getPosition();
                        float distSq = diff.x * diff.x + diff.y * diff.y;
                        float radiusSum = p1->getRadius() + p2->getRadius();

                        if (distSq < radiusSum * radiusSum) {
                            resolveCollision(*p1, *p2);
                        }
                    }
                }
            }
        }
    }
}

void getCollisions() {
    std::vector<std::pair<int, int>> allCells;
    for (const auto& [key, _] : PARTICLE_GRID) {
        allCells.push_back(key);
    }

    unsigned int numThreads = std::thread::hardware_concurrency();
    if (numThreads == 0) numThreads = 4;

    size_t chunkSize = allCells.size() / numThreads;
    std::vector<std::thread> threads;

    for (unsigned int i = 0; i < numThreads; ++i) {
        size_t start = i * chunkSize;
        size_t end = (i == numThreads - 1) ? allCells.size() : start + chunkSize;

        std::vector<std::pair<int, int>> threadCells(allCells.begin() + start, allCells.begin() + end);
        threads.emplace_back(processCellsRange, threadCells);
    }

    for (auto& t : threads) {
        t.join();
    }
}
