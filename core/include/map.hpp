#ifndef MAP_HPP
#define MAP_HPP

#include "island.hpp"

using namespace std;

typedef struct WorldMap {
    Graph graph;            //(change the type as per your implementation; this is just a placeholder); graph that represents the connections/relations between the islands.
    vector<Island> island;  //vector for islands; contains every possible parameter to set-up that island(coordinates, challenges, hints, random items, etc)
} WorldMap;

    generate_islands(int n);                //function to randomly generate position co-ordinates for n islands. -(almost done, needs some refinement)
    create_graph(int pos[][2]);             //given a 2-d array containing (x,y) co-ordinates of all islands, form a graph to represent connections between the islands.
    init_islands(vector<Island> island*);   //initialising the parameters for each islands
    get_all_within_distance_k();            //function to fetch all islands connected to current island and are at a given distance
                                        //add more functions as per requirement

#endif

