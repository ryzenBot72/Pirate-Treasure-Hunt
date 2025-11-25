#include "game_state.hpp"
#include "render.hpp"
#include "utils.hpp"
#include <cstdio>
#include <iostream> 

using namespace std;

//Initialise the GameState struct
void init_game_state(GameState *g_state) {
    PlayerState *p = &(g_state->p_state);
    DisplayState *d = &(g_state->d_state);

    d->mode = 1;
    d->show_map = false;
    
    // Reset display origin
    for(int i = 0; i < 3; i++) {
        d->disp[i][0] = 0;
        d->disp[i][1] = 0;
    }

    // Reset player position
    for(int i = 0; i < 3; i++) {
        p->pos[i][0] = 0;
        p->pos[i][1] = 0;
    }
    p->isAlive = true;
    p->x_max = DISPLAY_X;
    p->y_max = DISPLAY_Y;


    g_state->t_state.s += "Hello!\nNext line!\nDemo demoo demo demo demo demo demo demo demo demo demo demo demo demo demo demo demo demo demo demo demo demo demo demo demo demo demo!";

    g_state->isActive = 2;
    g_state->proximity = 1;
}


void build_text(GameState *g_state, WorldMap *map) {
    string *s = &(g_state->t_state.s);

    *s += sf("%3d%3d", g_state->p_state.pos[g_state->d_state.mode][0], g_state->p_state.pos[g_state->d_state.mode][1]);
    *s += sf("%3d\n", g_state->game_event.size());


    if(g_state->game_event.size() != 0) {
        queue<array<int,2>> temp = g_state->game_event;

        if(g_state->d_state.mode == 1) {
            *s += "\nDo you want to explore?\n";
        }
        else if (g_state->d_state.mode == 2) {
            *s += "\nExamine?\n";
        }

        for(int i = 1; !temp.empty(); i++) {
            *s += sf("%i\n", i);            
            temp.pop();
        }
    }
}



//changes the elements of the GameState struct as per the player key input
// Note: We are changing the signature slightly to 'int ch' based on leader's code
int state_manager(int ch, GameState *g_state, WorldMap *map) {
    DisplayState *d = &(g_state->d_state);
    PlayerState *p = &(g_state->p_state);

    int* x = &(p->pos[d->mode][0]);
    int* y = &(p->pos[d->mode][1]);

    //For arrow keys
    if(ch == 27) {  // Escape character
        ch = getchar();  // Get the next character
        if(ch == '[') {
            ch = getchar();  // Get the actual arrow key code
            switch (ch) {
                case 'A': //Up
                    if(*y > 0 && (*map->type[d->mode - 1])[1][*y - 1][*x] >= 2)
                        (*y)--;
                    break;
                case 'B': //Down
                    if(*y < p->y_max && (*map->type[d->mode - 1])[1][*y + 1][*x] >=  2)
                        (*y)++;
                    break;
                case 'C': //Right
                    if(*x < p->x_max && (*map->type[d->mode - 1])[1][*y][*x + 1] >= 2)
                        (*x)++;
                    break;
                case 'D': //Left
                    if(*x > 0 && (*map->type[d->mode - 1])[1][*y][*x - 1] >= 2)
                        (*x)--;
                    break;
            }
        }
    }
    else {
        switch (ch) {
            case 'm':   //toggling show_map
            case 'M': {
                if(d->mode == 1) {
                    d->mode = 2; // Blank
                }
                else if (d->mode == 2){
                    d->mode = 1; // Sea
                }/*
                else {
                    d->mode = 2; // Island
                }*/
                break;
            }
            
            //MEMBER C ADDITION
            case 'c':
            case 'C': {
                // Interaction Logic: Check / Collect Clue
                if(d->mode == 2) {
                    // We are in Island View. 
                    // Logic to check if this specific island has a clue would go here.
                    // For the prototype, we display a generic message or the first clue.
                    // In a full implementation, we would cross-reference player coordinates
                    // with the WorldMap island list.
                }
                break;
            }
            // -------------------------

            case 'e':   //closing the current game session
            case 'E':
                (g_state->isActive)--;
                break;
    

            case 'y':
         /*       
                if(g_state->proximity == 1 && g_state->game_event.size() > 0) {
                    trigger_event(&(g_state->game_event));
                }*/
                break;
        }
    }

    if(ch >= '1' && ch <= '9') {
        if(g_state->proximity == 1 && g_state->game_event.size() > 0) {
            while(ch > '1') {
                g_state->game_event.pop();
                ch--;
            }
            trigger_event(g_state->game_event.front(), map, g_state);
        }
    }

    // Boundary checks
    if(d->mode == 1) {
        p->x_max = SEA_OVERVIEW_X - 1;
        p->y_max = SEA_OVERVIEW_Y - 1;
    }
    else if(d->mode == 2) {
        p->x_max = ISLAND_X - 1;
        p->y_max = ISLAND_Y - 1;
    }


    while(!g_state->game_event.empty()) {
        g_state->game_event.pop();
    }

    scan_player_area(map, g_state);

    g_state->t_state.s.clear();
    build_text(g_state, map);

    return 0;
}
