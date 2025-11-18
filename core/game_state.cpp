#include "game_state.hpp"
#include "render.hpp"
#include <stdio.h>

//Initialise the GameState struct
void init_game_state(GameState *g_state) {
    PlayerState *p = &(g_state->p_state);
    DisplayState *d = &(g_state->d_state);

    d->mode = 1;
    d->show_map = false;
    for(int i = 0; i < 3; i++) {
        d->disp[i][0] = 0;
        d->disp[i][1] = 0;
    }

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
int state_manager(int ch, GameState *g_state) {
    DisplayState *d = &(g_state->d_state);
    PlayerState *p = &(g_state->p_state);

    int* x = &(p->pos[d->mode][0]);
    int* y = &(p->pos[d->mode][1]);

    //For arrow keys
    if(ch == 27) {  // Escape character
        ch = getchar();  // Get the next character in the sequence (arrow key)
        if(ch == '[') {
            ch = getchar();  // Get the actual arrow key code

            switch (ch) {
                case 'A':   //Up Arrow
                    if(*y > 0) (*y)--;
                    break;
                case 'B':   //Down Arrow
                    if(*y < p->y_max) (*y)++;
                    break;
                case 'C':   //Right Arrow
                    if(*x < p->x_max) (*x)++;
                    break;
                case 'D':   //Left Arrow
                    if(*x > 0) (*x)--;
                    break;
            }
        }
    }
    else {
        switch (ch) {
            case 'm':   //toggling show_map
            case 'M': {
                //g_state->d_state.show_map = !(g_state->d_state.show_map);
                if(d->mode == 1) {
                    d->mode = 0;
                }
                else if (d->mode == 2){
                    d->mode = 1;
                }
                else {
                    d->mode = 2;
                }

                break;
            }

            case 'e':   //closing the current game session
            case 'E':
                (g_state->isActive)--;
                break;
        }
    }

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
