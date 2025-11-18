#ifndef ISLAND_HPP
#define ISLAND_HPP

#include <vector>
#include <string> // Required for string

using namespace std;

// MEMBER C UPDATE START
// Defining the structure of a Clue
typedef struct Clue {
    int id;
    string riddle;      // The puzzle text
    string solution;    // The answer (optional, if you want input)
    bool isFound;       // Has the player found this yet?
} Clue;

typedef struct Events {
    int type;           // 0 = nothing, 1 = Clue, 2 = Trap
    string description;
    Clue clueData;      // Embed the clue inside the event
} Events;
//MEMBER C UPDATE END

typedef struct Items {
    //type of item, associated data 
    string name; // Added name
} Items;

typedef struct IslandStuff {
    vector<Events> events;  // Member C: Clues stored here
    vector<Items> items;    
} IslandStuff;

typedef struct Island {
    int id;
    int coords[2];          
    IslandStuff initial;
} Island;

#endif
