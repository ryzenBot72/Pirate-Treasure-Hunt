#include <cstdlib>
#include <ctime>
#include "map.hpp"
#include "utils.hpp"


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
            map->sea_overview[i][j] = 21;
        }
    }

    //islands
    for(size_t i = 0; i < map->island.size(); i++) {
        x = map->island[i].coords[0];
        y = map->island[i].coords[1];

        //mat[x][y] = 220; //Yellow
        map->sea_overview[y][x] = 34; //Green
    }
/*-------------------------------------*/


/*-----------ISLAND_NORMAL------------*/
    //land
    for(int i = 0; i < ISLAND_Y; i++) {
        for(int j = 0; j < ISLAND_X; j++) {
            map->island_normal[i][j] = 88;
        }
    }
/*-------------------------------------*/
}

void init_map(WorldMap *map) {
    generate_islands(map->island, 5);

    init_matrix(map);
}
