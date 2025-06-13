#include "globals.h"

float GRAVITY = 100.0f;
float ELASTIC_RESTITUTION = 0.7f;
float WINDOW_PADDING = 100.f;
int COLLISION_CELL_SIZE = 50;

std::unordered_map<std::pair<int, int>, std::vector<Particle *>, pair_hash> PARTICLE_GRID;