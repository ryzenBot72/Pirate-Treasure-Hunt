#include "render.hpp"
#include <iostream>

//print the matrix representing the game display
void printMatrix(int rows, int cols, const vector<vector<vector<int>>>& matrix, GameState *g_state, WorldMap *map) {
    int (*pos)[2] = g_state->p_state.pos;
    int (*disp)[2] = g_state->d_state.disp;
    DisplayState *d = &(g_state->d_state);

    // Change the coordinates of the 'display point(matrix[0][0])' based on the postion of the player on the map.
    if(pos[d->mode][0] >= (DISPLAY_X - 1)/2) {
        if(pos[d->mode][0] < cols - (DISPLAY_X/2)) {
            disp[d->mode][0] = pos[d->mode][0] - (DISPLAY_X - 1)/ 2;
        }
        else {
            disp[d->mode][0] = cols - (DISPLAY_X);
        }
    }
    else {
        disp[d->mode][0] = 0;
    }
 
    if(pos[d->mode][1] >= (DISPLAY_Y - 1)/2) {
        if(pos[d->mode][1] < rows - (DISPLAY_Y/2)) {
            disp[d->mode][1] = pos[d->mode][1] - (DISPLAY_Y - 1)/ 2;
        }
        else {
            disp[d->mode][1] = rows - (DISPLAY_Y);
        }
    }
    else {
        disp[d->mode][1] = 0;
    }

    //printing the actual diplay matrix using the 'display point'
    for(int i = disp[d->mode][1], k = 0; i < disp[d->mode][1] + DISPLAY_Y; i++) {
        for(int j = disp[d->mode][0]; j < disp[d->mode][0] + DISPLAY_X; j++) {
            printf("\x1b[38;5;0m");
            if(j == pos[d->mode][0] && i == pos[d->mode][1]) {
                printf("\x1b[48;5;%dm", proximity_color(g_state, map));   //Player icon
            }
            else {
                printf("\x1b[48;5;%dm", matrix[0][i][j]);   //Rest of the map boxes
            }

            int id = find_island(map, j, i);

            if(d->mode == 1 && id >= 0) {
                printf(" %d", id);
            }
            else if(d->mode == 2 && map->island[map->clue_start].initial.items.size() != 0 && j == map->island[map->clue_start].initial.items[0].pos[0] && i == map->island[map->clue_start].initial.items[0].pos[1]) {
                printf(" #");
                k++;
            }
            else if (d->mode == 2 && k < (int)g_state->game_event.size() && j == g_state->game_event[k][0] && i == g_state->game_event[k][1]) {
                printf(" %d", k + 1);
                k++;
            }
            else
                printf("%2c", ' ');

            #ifdef __linux__
                printf(" ");
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
                    printMatrix(SEA_OVERVIEW_Y, SEA_OVERVIEW_X, map->sea_overview, g_state, map);
                    break;
                }
        case 2: {
                    printMatrix(ISLAND_Y, ISLAND_X, map->island_canvas, g_state, map);
                    break;
                }
    }
}

void printText(GameSession* game) {
    string *s = &(game->g_state.t_state.s);

    int limit;
    #if defined (_WIN32)
        limit = DISPLAY_X * 2;
    #else
        limit = DISPLAY_X * 3;
    #endif

    printf("\x1b[48;5;0m");

    for(int i = 0, j = 0, k = 0; (*s)[i] != 0;) {
        while((*s)[j] != ' ' && (*s)[j] != '\n' && (*s)[j] != 0 && (*s)[j] != '\x1b') {
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
            else if((*s)[j] == '\x1b') {
                i = j;
                while((*s)[j] != 'm') {
                    putchar((*s)[j++]);
                    //k -= j - i;
                }
                putchar('m');
                j++;
                i = j;
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


    printf("\x1b[0m");
}

//Display the game
void render(unique_ptr<World>& w) {
    //Position the cursor at row 1, col 1
    printf("\x1b[H");
    
    //Print the game display
    printDisplay(&(w->map), &(w->game[0].g_state));
    
    //Print the game text or dialogue
    printText(&(w->game[0]));

    // Clear from the cursor to the end of screen
    printf("\x1b[0J");

    //To immediately display the content present in the output buffer
    fflush(stdout);
}
