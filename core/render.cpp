#include "render.hpp"

//print the matrix representing the game display
void printMatrix(int rows, int cols, const vector<vector<int>>& matrix, GameState *g_state) {
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
                printf("\x1b[48;5;%dm", matrix[i][j]);
            }
            printf("%3c", ' ');
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
    printf("\x1b[48;5;0m");
    printf("%3d%3d", game->g_state.p_state.pos[game->g_state.d_state.mode][0], game->g_state.p_state.pos[game->g_state.d_state.mode][1]);
    for(int i = 0; i < DISPLAY_X - 2; i++) {
        printf("%3c", ' ');
    }
    printf("\x1b[0m\n");
}

//Display the game
void render(unique_ptr<World>& w) {
    printf("\x1b[1;1H\x1b[2J\x1b[3J");      //clear the entire screen

    printDisplay(&(w->map), &(w->game[0].g_state));     //print the game display

    printText(&(w->game[0]));     //print the game text or dialogue
}
