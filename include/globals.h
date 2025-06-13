#pragma once

#include <unordered_map>
#include <utility>  // for std::pair
#include <vector>

#include "pair_hash.h"  // you'll define this for std::pair hash support
#include "particle.h"   // needed for Particle*

extern float GRAVITY;
extern float ELASTIC_RESTITUTION;
extern float WINDOW_PADDING;
extern int COLLISION_CELL_SIZE;

extern std::unordered_map<std::pair<int, int>, std::vector<Particle *>, pair_hash> PARTICLE_GRID;
