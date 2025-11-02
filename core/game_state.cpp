#include "game_state.hpp"
#include <stdio.h>

//Initialise the GameState struct
void init_game_state(GameState *g_state) {
    PlayerState *p = &(g_state->p_state);
    DisplayState *d = &(g_state->d_state);

    p->pos[0] = 0;
    p->pos[1] = 0;
    p->isAlive = true;
    p->top_allowed = true;
    p->bottom_allowed = true;
    p->right_allowed = true;
    p->left_allowed = true;

    d->mode = 1;
    d->show_map = false;

    g_state->isActive = 2;
}

//changes the elements of the GameState struct as per the player key input
int state_manager(char ch, GameState *g_state) {

    //For arrow keys
    if(ch == 27) {  // Escape character
        ch = getchar();  // Get the next character in the sequence (arrow key)
        if(ch == '[') {
            ch = getchar();  // Get the actual arrow key code

            int* x = &(g_state->p_state.pos[0]);
            int* y = &(g_state->p_state.pos[1]);
            PlayerState* p = &(g_state->p_state);
            switch (ch) {
                case 'A':   //Up Arrow
                    if(p->top_allowed) (*y)--;
                    break;
                case 'B':   //Down Arrow
                    if(p->bottom_allowed) (*y)++;
                    break;
                case 'C':   //Right Arrow
                    if(p->right_allowed) (*x)++;
                    break;
                case 'D':   //Left Arrow
                    if(p->left_allowed) (*x)--;
                    break;
            }
        }
    }
    else {
        switch (ch) {
            case 'm':   //toggling show_map
            case 'M': {
                          g_state->d_state.show_map = !(g_state->d_state.show_map);
                          break;
                      }

            case 'e':   //closing the current game session
            case 'E': {
                          /*if(g_state->isActive == 2) {
                            g_state->isActive = 1;
                            }
                            else if(g_state->isActive == 1) {
                            g_state->isActive = 0;
                            }*/
                          (g_state->isActive)--;

                          break;
                      }
        }
    }

    return 0;
}
