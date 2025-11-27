#include "render.hpp"
#include <iostream>

//print the matrix representing the game display
void printMatrix(int rows, int cols, const vector<vector<vector<int>>>& matrix, GameState *g_state) {
    int (*pos)[2] = g_state->p_state.pos;
    int (*disp)[2] = g_state->d_state.disp;
    DisplayState *d = &(g_state->d_state);

    //if statements to change the coordinates of the 'display point(matrix[0][0])' based on the postion of the player on the map.
    if(pos[d->mode][0] >= (DISPLAY_X - 1)/2 && pos[d->mode][0] < cols - (DISPLAY_X/2)) {
        disp[d->mode][0] = pos[d->mode][0] - (DISPLAY_X - 1)/ 2;
    }
    if(pos[d->mode][1] >= (DISPLAY_Y - 1)/2 && pos[d->mode][1] < rows - (DISPLAY_Y/2)) {
        disp[d->mode][1] = pos[d->mode][1] - (DISPLAY_Y - 1)/ 2;
    }

    //printing the actual diplay matrix using the 'display point'
    for(int i = disp[d->mode][1]; i < disp[d->mode][1] + DISPLAY_Y; i++) {
        for(int j = disp[d->mode][0]; j < disp[d->mode][0] + DISPLAY_X; j++) {
            if(j == pos[d->mode][0] && i == pos[d->mode][1]) {
                printf("\x1b[48;5;160m");
            }
            else {
                printf("\x1b[48;5;%dm", matrix[0][i][j]);
            }
            #ifdef _WIN32
                printf("%2c", ' ');
            #else
                printf("%3c", ' ');
            #endif
            printf("\x1b[0m");
        }
        printf("\n");
    }
}

void printDisplay(WorldMap *map, GameState *g_state) {
    switch (g_state->d_state.mode) {
        case 0: {
                    break;
                }
        case 1: {
                    printMatrix(SEA_OVERVIEW_Y, SEA_OVERVIEW_X, map->sea_overview, g_state);
                    break;
                }
        case 2: {
                    printMatrix(ISLAND_Y, ISLAND_X, map->island_normal, g_state);
                    break;
                }
    }
}

void printText(GameSession* game) {
    string *s = &(game->g_state.t_state.s);
    bool stop = false;
    int limit = DISPLAY_X * 3;
    printf("\x1b[48;5;0m");
/*
    do{
        printf("%3d%3d", game->g_state.p_state.pos[game->g_state.d_state.mode][0], game->g_state.p_state.pos[game->g_state.d_state.mode][1]);
        printf("%3lu", game->g_state.game_event.size());
        
        stop = true;
        for(int i = 0; i < DISPLAY_X - 2; i++) {
            #ifdef _WIN32
                printf("%2c", ' ');
            #else
                printf("%3c", ' ');
            #endif
        }
    } while(!stop);*/

    for(int i = 0, j = 0, k = 0; (*s)[i] != 0;) {
        while((*s)[j] != ' ' && (*s)[j] != '\n' && (*s)[j] != 0) {
            j++;
        }

        if(k + (j - i) == limit) {
            while(i < j) {
                putchar((*s)[i++]);
            }

            if((*s)[i] == 0) {
                break;
            }
            putchar('\n');

            i++;
            j = i;
            k = 0;
            continue;
        }
        else if(k + (j - i) > limit) {
            j = i;

            while(k < limit) {
                putchar(' ');
                k++;
            }
            putchar('\n');
            k = 0;
        }
        else {
            while(i < j) {
                putchar((*s)[i]);
                k++;
                i++;
            }
            if((*s)[j] == '\n') {
                i++;
                j = i;
                
                while(k < limit) {
                    putchar(' ');
                    k++;
                }
                putchar('\n');
                k = 0;

            }
            else if((*s)[j] == 0) {
                i = j;

                while(k < limit) {
                    putchar(' ');
                    k++;
                }
                //putchar('\n');
                k = 0;

                continue;
            }
            else {
                putchar(' ');
                i++;
                k++;
                j = i;
                continue;
            }
        }
    }


    printf("\x1b[0m\n");
}

//Display the game
void render(unique_ptr<World>& w) {
    printf("\x1b[1;1H\x1b[2J\x1b[3J");      //clear the entire screen

    printDisplay(&(w->map), &(w->game[0].g_state));     //print the game display

    printText(&(w->game[0]));     //print the game text or dialogue

    fflush(stdout);        //to immediately display the content within the output buffer
}
