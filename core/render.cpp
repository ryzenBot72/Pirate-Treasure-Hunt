#include "render.hpp"

//print the matrix representing the game display
void printMatrix(int (*matrix)[X_MAX], int *pos) {
    for(int i = 0; i < Y_MAX; i++) {

        for(int j = 0; j < X_MAX; j++) {
            if(j == pos[0] && i == pos[1]) {
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

    printf("%d %d\n", pos[0], pos[1]);
}

void printDisplay(WorldMap *map, GameState *g_state) {
    switch (g_state->d_state.mode) {
        case 0: {
                    break;
                }
        case 1: {
                    printMatrix(map->matrix, g_state->p_state.pos);
                    break;
                }
    }
}

//Display the game
void render(World *w) {
    printf("\x1b[1;1H\x1b[2J\x1b[3J");      //clear the entire screen
    printDisplay(&(w->map), &(w->game[0].g_state));     //print the game display
    //printText();      //print the game text or dialogue
}
