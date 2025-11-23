#include "game_state.hpp"
#include "render.hpp"
#include <stdio.h>
#include <iostream>

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

    g_state->isActive = 2;
}

//changes the elements of the GameState struct as per the player key input
// Note: We are changing the signature slightly to 'int ch' based on leader's code
int state_manager(int ch, GameState *g_state) {
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
                case 'A': if(*y > 0) (*y)--; break; // Up
                case 'B': if(*y < p->y_max) (*y)++; break; // Down
                case 'C': if(*x < p->x_max) (*x)++; break; // Right
                case 'D': if(*x > 0) (*x)--; break; // Left
            }
        }
    }
    else {
        switch (ch) {
            case 'm':   //toggling show_map
            case 'M': {
                if(d->mode == 1) {
                    d->mode = 0; // Blank
                }
                else if (d->mode == 2){
                    d->mode = 1; // Sea
                }
                else {
                    d->mode = 2; // Island
                }
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

    return 0;
}
