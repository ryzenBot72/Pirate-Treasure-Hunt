#include <cstdlib>
#include <ctime>
#include <math.h>
#include "map.hpp"
#include "utils.hpp"


//selects a number(tile color) from an array randomly
int random_tile(int type) {
    int tile[2][5] = {{39, 33, 39, 33, 39}, {240, 76, 220, 112, 112}};

    return tile[type - 1][(int)sqrt(rand() % 25)];
}

//randomly generate 'n' islands
void generate_islands(vector<Island>& island, int n) {
    srand(time(0));
    for(int i = 0; i < n; i++) {
        island.push_back(Island());

        island[i].coords[0] = rand() % SEA_OVERVIEW_X;
        island[i].coords[1] = rand() % SEA_OVERVIEW_Y;
    }
}

//initialising the ANSI color values at each matrix location
void init_matrix(WorldMap *map) {
    int x,y;

/*------------SEA_OVERVIEW-------------*/
    //water
    srand(time(0));
    for(int i = 0; i < SEA_OVERVIEW_Y; i++) {
        //srand(time(0));
        for(int j = 0; j < SEA_OVERVIEW_X; j++) {
            //map->sea_overview[i][j] = 21;
            map->sea_overview[i][j] = random_tile(1);
        }
    }

    //islands
    for(size_t i = 0; i < map->island.size(); i++) {
        x = map->island[i].coords[0];
        y = map->island[i].coords[1];

        //mat[x][y] = 220; //Yellow
        map->sea_overview[y][x] = 40; //Green
    }
/*-------------------------------------*/


/*-----------ISLAND_NORMAL------------*/
    //land
    for(int i = 0; i < ISLAND_Y; i++) {
        for(int j = 0; j < ISLAND_X; j++) {
            //map->island_normal[i][j] = 88;
            map->island_normal[i][j] = random_tile(2);
        }
    }
/*-------------------------------------*/
}

void init_map(WorldMap *map) {
    generate_islands(map->island, 5);

    init_matrix(map);
}
