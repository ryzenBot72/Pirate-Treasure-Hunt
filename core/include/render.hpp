#ifndef RENDER_HPP
#define RENDER_HPP

#include "world.hpp"

void printMatrix(int (*matrix)[X_MAX], int *pos);
void printDisplay(WorldMap *map, GameState *g_state);
void render(World *w);

#endif
