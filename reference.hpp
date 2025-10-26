/*  NOTE: This file is just for reference. It contains the general structure of all the header files to be used in the game. This file will not be included int the final game.
 *  Each section represents a seperate header file
 *  If you want to add a new header in the game's file structure, please put the name and basic use of it here as well.
 */

#include <vector>       //for vector in World
#include <string>       //for string in World

using namespace std;


//--------------Player--------------
typedef struct Inventory {
    //Add items here
} Inventory;

typedef struct Player {
    Inventory inventory;    //all inventory related stuff here
} Player;
//-------------End_Player---------------


//--------------Game_state--------------
#include "island.hpp"

typedef struct IslandState {
    int id;
    bool isVisible;         //is the island visible on the map(yes/no)
    IslandStuff pending;    //to be initialised at the beginning of the game session using the default values in the island struct
    IslandStuff visited;
} IslandState;

typedef struct PlayerState {
    bool isAlive;
    int pos[2];         //(x,y) coordinates of the player
    vector<int> visited;
    float energy;
    float deplete_rate;
} PlayerState;

typedef struct DisplayState{
    int mode;           //ex.(0 - blank, 1 - sea, 2 - island, 3 - challenge)
    bool show_map;      //(0 - normal game screen, 1 - overview of the map based on the display mode)
} DisplayState;

typedef struct TextState{
    bool show_text;     //(0 - no text, 1 - display text)
                        //some more variables to be added
} TextState;

typedef struct GameState {
    vector<IslandState> i_state;    //island visibility, status of items and challeges(how many challenges completed/ items received/ how many are left) per island
    PlayerState p_state;            //current position, islands visited, alive/dead, energy, energy_deplete_rate(depends upon display state + abilities), progress(optional) \
                                      (note, pixel to pixel jump speed will be the same for each display state, just the step size would vary, thus varing the energy consumption)
    DisplayState d_state;           //sea_mode, island_mode, challenge_mode, view_island/view_sea(birds-eye view of the island/sea)
    TextState t_state;              //enable/disable text menu, what to display in the text area. 
} GameState;
//------------End_Game_state-----------


//------------Game_session------------
#include "player.hpp"
#include "game_state.hpp"

typedef struct GameSession {
    int id;
    string name;            //name of the game session/player
    Player player;          //data associated with the player(inventory, abilities)
    GameState g_state;      //States of all the entities of the game
} GameSession;
//-----------End_Game_session--------------


//--------------Island--------------
typedef struct Events {
    //event type, all the relevent data
} Events;

typedef struct Items {
    //type of item, associated data 
} Items;

typedef struct IslandStuff {
    vector<Events> events;  //challenges, direct hints
    vector<Items> items;    //random items (along with their position maybe?)
} IslandStuff;

typedef struct Island {
    int id;
    int coords[2];          //x,y coordinates of the island
    IslandStuff initial;
} Island;
//-----------End_Island---------------


//--------------Map----------------
#include "island.hpp"

typedef struct WorldMap {
    Graph graph;            //(change the type as per your implementation; this is just a placeholder); graph that represents the connections/relations between the islands.
    vector<Island> island;  //vector for islands; contains every possible parameter to set-up that island(coordinates, challenges, hints, random items, etc)
} WorldMap;

    generate_islands(int n);                //function to randomly generate position co-ordinates for n islands. -(almost done, needs some refinement)
    create_graph(int pos[][2]);             //given a 2-d array containing (x,y) co-ordinates of all islands, form a graph to represent connections between the islands.
    init_islands(vector<Island> island*);   //initialising the parameters for each islands
    get_all_within_distance_k();            //function to fetch all islands connected to current island and are at a given distance
                                            //add more functions as per requirement
//-------------End_Map--------------


//-------------World------------
//As each world will contain a unique randomly generated map, seperating the different worlds makes sense
#include "game_session.hpp"
#include "map.hpp"

typedef struct World {
    string name;                //name of the world
    vector<GameSession> game;   //each game session is associated to a unique player
    WorldMap map;               //common to all the players of the current world
} World;
//-----------End_World------------
