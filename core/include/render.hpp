#ifndef RENDER_HPP
#define RENDER_HPP

#include "world.hpp"

#define DISPLAY_X 30
#define DISPLAY_Y 30

void printMatrix(int rows, int cols, const vector<vector<int>>& matrix, GameState *g_state);
void printDisplay(WorldMap *map, GameState *g_state);
void printText(GameSession* game);
void render(unique_ptr<World>& w);

#endif
