#ifndef ISLAND_HPP
#define ISLAND_HPP

#include <vector>
#include <string> // Required for string

using namespace std;

// MEMBER C
// Defining the structure of a Clue
typedef struct Clue {
    int id;
    int island_id;
    string riddle;      // The puzzle text
    string key;    // The answer (optional, if you want input)
    bool isFound;       // Has the player found this yet?
} Clue;

typedef struct Event {
    int type;           // 0 = nothing, 1 = Clue, 2 = Trap
    int pos[2];
    string name;
    string description;
    Clue clueData;      // Embed the clue inside the event
} Events;

// --- MEMBER A: Item Definition ---
typedef struct Item {
    string name;
    string description;
    int value; // Gold value or Energy restore amount
    int pos[2];
} Item;
// ---------------------------------

typedef struct IslandStuff {
    vector<Event> events;  // Member C: Clues stored here
    vector<Item> items;    
} IslandStuff;

typedef struct Island {
    int id;
    int coords[2];          
    IslandStuff initial;
} Island;

#endif
