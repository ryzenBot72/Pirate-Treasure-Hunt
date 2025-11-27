#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <string>
#include <algorithm>
#include "game_state.hpp"
#include "island.hpp" // Need this to know what a 'Clue' is

using namespace std;

typedef struct Inventory {
    //MEMBER C UPDATE
    // A dynamic list (Vector) to store collected clues.
    // This represents a Linear Data Structure.
    vector<Clue> collected_clues; 
    // -----------------------

    // --- MEMBER A: Items ---
    // A dynamic list (Vector) to store general items.
    vector<Item> items;

    // Helper to add an item
    void addItem(Item item) {
        items.push_back(item);
    }

    // Helper to remove an item by name
    void removeItem(string itemName) {
        // Lambda function to find item by name
        auto it = remove_if(items.begin(), items.end(), 
            [&](const Item& i) { return i.name == itemName; });

        // Erase the removed items
        if (it != items.end()) {
            items.erase(it, items.end());
        }
    }
    // -----------------------

} Inventory;

typedef struct Player {
    Inventory inventory;    
} Player;

void scan_player_area(WorldMap *map, GameState *g_state);

#endif
