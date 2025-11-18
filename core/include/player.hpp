#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <string>
#include "island.hpp" // Need this to know what a 'Clue' is

using namespace std;

typedef struct Inventory {
    //MEMBER C UPDATE
    // A dynamic list (Vector) to store collected clues.
    // This represents a Linear Data Structure.
    vector<Clue> collected_clues; 
    // -----------------------
} Inventory;

typedef struct Player {
    Inventory inventory;    
} Player;

#endif
