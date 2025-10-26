#ifndef WORLD_HPP
#define WORLD_HPP

//As each world will contain a unique randomly generated map, seperating the different worlds makes sense
#include <vector>
#include "game_session.hpp"
#include "map.hpp"

using namespace std;

typedef struct World {
    string name;                //name of the world
    vector<GameSession> game;   //each game session is associated to a unique player
    WorldMap map;               //common to all the players of the current world
} World;

#endif
