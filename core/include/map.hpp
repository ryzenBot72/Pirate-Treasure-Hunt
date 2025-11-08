#ifndef MAP_HPP
#define MAP_HPP

#include "island.hpp"

using namespace std;

#define SEA_OVERVIEW_X 41
#define SEA_OVERVIEW_Y 41
#define ISLAND_X 40
#define ISLAND_Y 40

typedef struct WorldMap {
    //Graph graph;            //(change the type as per your implementation; this is just a placeholder); graph that represents the connections/relations between the islands.
    vector<Island> island;  //vector for islands; contains every possible parameter to set-up that island(coordinates, challenges, hints, random items, etc)
        
    vector<vector<int>> sea_overview{SEA_OVERVIEW_Y, vector<int>(SEA_OVERVIEW_X, 0)};
    vector<vector<int>> island_normal{ISLAND_Y, vector<int>(ISLAND_X, 0)};

} WorldMap;
    
    void generate_islands(vector<Island>& island, int n);                //function to randomly generate position co-ordinates for n islands. -(almost done, needs some refinement)
    void create_graph(int pos[][2]);             //given a 2-d array containing (x,y) co-ordinates of all islands, form a graph to represent connections between the islands.
    void init_islands(vector<Island>& island);   //initialising the parameters for each islands
    void get_all_within_distance_k();            //function to fetch all islands connected to current island and are at a given distance
                                        //add more functions as per requirement
    void init_map(WorldMap *map);
#endif

