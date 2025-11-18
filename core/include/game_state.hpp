#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "island.hpp"

using namespace std;

typedef struct IslandState {
    int id;
    bool isVisible;         //is the island visible on the map(yes/no)
    IslandStuff pending;    //to be initialised at the beginning of the game session using the default values in the island struct
    IslandStuff visited;
} IslandState;

typedef struct PlayerState {
    bool isAlive;
    int pos[3][2];      //(x,y) coordinates of the player
    vector<int> visited;
    float energy;
    float deplete_rate;
    int x_max;          //x-direction limit of the player movement(x boundary of the map)
    int y_max;          //y-direction limit of the player movement(y boundary of the map)

} PlayerState;

typedef struct DisplayState{
    int mode;           //ex.(0 - blank, 1 - sea, 2 - island, 3 - challenge)
    bool show_map;      //(0 - normal game screen, 1 - overview of the map based on the display mode)
    int disp[3][2];     //stores the position of the origin point(0,0) of the display matrix w.r.t. to the map
} DisplayState;

typedef struct TextState{
    bool show_text;     //(0 - no text, 1 - display text)
                        //some more variables to be added
} TextState;

typedef struct GameState {
    int isActive;                   //is the game session active(0 : close game session; 1: show closing confirmation window; 2 : game session is running)
    vector<IslandState> i_state;    //island visibility, status of items and challeges(how many challenges completed/ items received/ how many are left) per island
    PlayerState p_state;            /*current position, islands visited, alive/dead, energy, energy_deplete_rate(depends upon display state + abilities), progress(optional)
                                      (note, pixel to pixel jump speed will be the same for each display state, just the step size would vary, thus varing the energy consumption) */
    DisplayState d_state;           //sea_mode, island_mode, challenge_mode, view_island/view_sea(birds-eye view of the island/sea)
    TextState t_state;              //enable/disable text menu, what to display in the text area. 
} GameState;


void init_game_state(GameState *g_state);

int state_manager(int ch, GameState *g_state);

#endif

