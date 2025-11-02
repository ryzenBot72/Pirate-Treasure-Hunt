#include <cstdlib>
#include <ctime>
#include "map.hpp"
#include "utils.hpp"


//randomly generate 'n' islands
void generate_islands(vector<Island>& island, int n) {
    srand(time(0));
    for(int i = 0; i < n; i++) {
        island.push_back(Island());

        island[i].coords[0] = rand() % X_MAX;
        island[i].coords[1] = rand() % Y_MAX;
    }
}

//initialising the ANSI color values at each matrix location
void init_matrix(WorldMap *map) {
    int (*mat)[X_MAX];
    mat = (map->matrix);
    int x,y;


    //ocean
    for(int i = 0; i < Y_MAX; i++) {
        for(int j = 0; j < X_MAX; j++) {
            mat[i][j] = 21;
        }
    }

    //islands
    for(size_t i = 0; i < map->island.size(); i++) {
        x = map->island[i].coords[0];
        y = map->island[i].coords[1];

        //mat[x][y] = 220; //Yellow
        mat[x][y] = 34; //Green
    }
}

void init_map(WorldMap *map) {
    generate_islands(map->island, 5);

    init_matrix(map);
}
